/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:15:44 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/08 21:06:04 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redir.h"
#include "wrappers.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

extern volatile int	g_sig;

bool	ctrl_c_catched(char *line, int fd, char *filename, t_data *data)
{
	if (g_sig == 1)
	{
		if (line)
			free(line);
		close(fd);
		unlink(filename);
		w_signal(SIGINT, SIG_IGN, data);
		rl_event_hook = NULL;
		return (true);
	}
	return (false);
}

bool	eof_catched(char *line, int fd, t_redir *redir, t_data *data)
{
	if (!line || !ft_strcmp(handle_expand(line, 0, 0, data), redir->delimiter))
	{
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
			ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(redir->delimiter, STDERR_FILENO);
			ft_putendl_fd("')", STDERR_FILENO);
		}
		close(fd);
		w_signal(SIGINT, SIG_IGN, data);
		rl_event_hook = NULL;
		return (true);
	}
	return (false);
}
