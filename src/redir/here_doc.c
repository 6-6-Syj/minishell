/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:14:12 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/08 19:02:13 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "handle_signal.h"
#include "libft.h"
#include "redir.h"
#include "wrappers.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <token.h>
#include <unistd.h>

extern volatile int	g_sig;

static void	init_heredoc_sig_handler(t_data *data)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) != -1)
	{
		ft_putendl_fd("minishell: sigaction failed", STDERR_FILENO);
		data->err = 6;
		return ;
	}
	w_signal(SIGQUIT, SIG_IGN, data);
}

static int	open_heredoc_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell: open");
	return (fd);
}

static int	read_heredoc_loop(t_redir *redir, t_data *data)
{
	char	*line;
	int		fd;

	fd = open_heredoc_file(redir->filename);
	if (fd < 0)
		return (-1);
	init_heredoc_sig_handler(data);
	while (g_sig == 0)
	{
		rl_event_hook = event_hook;
		line = readline("> ");
		if (ctrl_c_catched(line, fd, redir->filename, data))
			return (-1);
		if (eof_catched(line, fd, redir, data))
			return (0);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	unlink(redir->filename);
	w_signal(SIGINT, SIG_IGN, data);
	rl_event_hook = NULL;
	return (-1);
}

static char	*get_filename(t_data *data)
{
	char		*counter_str;
	char		*filename;
	static int	count;

	count = 0;
	counter_str = ft_itoa(count++);
	filename = ft_strjoin("/tmp/here_doc_", counter_str);
	free(counter_str);
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		counter_str = ft_itoa(count++);
		filename = ft_strjoin("/tmp/here_doc_", counter_str);
		free(counter_str);
		if (!filename)
			malloc_fail(data);
	}
	return (filename);
}

void	set_here_doc(t_redir **redir_node, t_data *data)
{
	int		ret;
	char	*filename;

	if (g_sig != 0)
		return ;
	filename = get_filename(data);
	(*redir_node)->filename = filename;
	if (!(*redir_node)->filename)
		return ;
	ret = read_heredoc_loop(*redir_node, data);
	if (ret < 0)
		return ;
	if (ret == 0)
		g_sig = 0;
}
