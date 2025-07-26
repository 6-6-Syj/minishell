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

// void	set_here_doc(t_redir **redir_node, char * t_data *data)
// {
// 	set_filename();
// 		get_filename();
// 		open_here_doc();
// 	read_here_doc();
// }

// char	*get_filename_here_doc(char *path, char *key)
// {
// 	char	*filename;

// 	while (1)
// 	{
// 		filename = ft_strjoin(path, key);
// 		if (access(filename, F_OK) == -1)
// 			return (filename);
// 		// key = get_new_key();
// 	}
// 	return (filemame);
// }

// static bool	sig_handler_heredoc(char *line, int fd, t_redir **redir_node)
// {
// 	if (g_sig == SIGINT || !line)
// 	{
// 		close(fd);
// 		unlink((*redir_node)->filename);
// 		return (true);
// 	}
// }

static void	setup_heredoc_signal_handlers(struct sigaction *oldint)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, oldint);
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

static int	read_heredoc_loop(t_redir *redir)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open_heredoc_file(redir->filename);
	if (fd < 0)
		return (-1);
	while (g_sig != 1)
	{
		if (g_sig)
		{
			close(fd); // close ALL heredoc not one / ctrl c
			unlink(redir->filename);
			return (-2);
		}
		write(1, "> ", 2);
		line = get_next_line(0);
		if (g_sig)
		{
			if (line)
				free(line);
			close(fd);
			unlink(redir->filename);
			return (-1);
		}
		if (!line)
		{
			close(fd);
			ft_putstr_fd("\nminishell: warning: here-document ", STDERR_FILENO);
			ft_putstr_fd("delimited by end-of-file: ", STDERR_FILENO);
			ft_putstr_fd(redir->delimiter, STDERR_FILENO);
			return (0);
		}
		if (ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			close(fd);
			return (0);
		}
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
	}
	return (-2);
}

void	set_here_doc(t_redir **redir_node)
{
	struct sigaction	oldint;
	struct termios		saved_termios;
	int					ret;

	if (g_sig == 0)
	{
		(*redir_node)->filename = ft_strdup("/tmp/here_doc_test");
		if (!(*redir_node)->filename)
			return ;
		if (disable_ctrl_backslash(&saved_termios) == -1)
			return ;
		setup_heredoc_signal_handlers(&oldint);
		ret = read_heredoc_loop(*redir_node);
		if (ret < 0)
		{
			g_sig = 1;
			return ;
		}
		sigaction(SIGINT, &oldint, NULL);
		signal(SIGQUIT, SIG_DFL);
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}
