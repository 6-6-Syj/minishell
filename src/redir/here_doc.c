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

char *get_here_doc_id(void)
{
	int	i;
	int	fd;
	char	*id;
	char	c_buff;
	
	i = 0;
	id = ft_calloc(4, sizeof(char));
	fd = open("/dev/urandom", O_RDONLY); // TODO: secu
	while (i < 4)
	{
		read(fd, &c_buff, 1); // TODO: secu
		if (ft_isdigit(c_buff))
			id[i++] = c_buff;
	}
	close(fd);
	return (id);
}

char *get_here_doc_filename(void)
{
	// char	*id;
	char	*filename;

	filename = ft_strjoin("tmp/here_doc", get_here_doc_id());
	ft_printf("filename = %s\n", filename);
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		filename = ft_strjoin("tmp/here_doc", get_here_doc_id());
	}
	return (filename);
}

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
	g_sig = 0;
	while (1)
	{
		if (g_sig)
		{
			close(fd); // close ALL heredoc not one / ctrl c
			unlink(redir->filename);
			return (-42);
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
			ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
			ft_putstr_fd("delimited by end-of-file\n", STDERR_FILENO);
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
}

void	set_here_doc(t_redir **redir_node, t_data *data)
{
	struct sigaction	oldint;
	struct termios		saved_termios;
	int					ret;

	(void)data;
	(*redir_node)->filename = ft_strdup("/tmp/here_doc_test");
	if (!(*redir_node)->filename)
		return ;
	if (disable_ctrl_backslash(&saved_termios) == -1)
		return ;
	setup_heredoc_signal_handlers(&oldint);
	ret = read_heredoc_loop(*redir_node);
	sigaction(SIGINT, &oldint, NULL);
	signal(SIGQUIT, SIG_DFL);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	g_sig = 0;
	if (ret == -42)
		ft_printf("here_doc.c, L154 - Need to stop the exec of the cmd\n");
}
