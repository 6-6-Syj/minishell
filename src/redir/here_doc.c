#include "handle_signal.h"
#include "minishell.h"
#include "redir.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <token.h>
#include <unistd.h>

extern volatile int	g_sig;

static void	init_heredoc_sig_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_putstr_fd("sigaction failed\n", STDERR_FILENO);
		return ;
	}
	signal(SIGQUIT, SIG_IGN);
}

static int	open_heredoc_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		perror("open");
	return (fd);
}

static bool	ctrl_c_catched(char *line, int fd, char *filename)
{
	if (g_sig == 1)
	{
		if (line)
			free(line);
		close(fd);
		unlink(filename);
		return (true);
	}
	return (false);
}

static bool	eof_catched(char *line, int fd, t_redir *redir, t_data *data)
{
	if (!line || !ft_strcmp(handle_expand(line, data), redir->delimiter))
	{
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
			ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(redir->delimiter, STDERR_FILENO);
			ft_putstr_fd("')\n", STDERR_FILENO);
		}
		close(fd);
		signal(SIGINT, SIG_IGN);
		return (true);
	}
	return (false);
}

static int	read_heredoc_loop(t_redir *redir, t_data *data)
{
	char	*line;
	int		fd;

	fd = open_heredoc_file(redir->filename);
	if (fd < 0)
		return (-1);
	init_heredoc_sig_handler();
	while (g_sig == 0)
	{
		signal(SIGINT, sig_handler_heredoc);
		line = readline("> ");
		if (ctrl_c_catched(line, fd, redir->filename))
			return (-1);
		if (eof_catched(line, fd, redir, data))
			return (0);
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	unlink(redir->filename);
	signal(SIGINT, SIG_IGN);
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
