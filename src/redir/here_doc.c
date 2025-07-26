#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <token.h>

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

void	set_here_doc(t_redir **redir_node, t_data *data)
{
	char	*line;
	int	fd;

	// printf("delimiter = %s\n", (*redir_node)->delimiter);
	(*redir_node)->filename = get_here_doc_filename();
	fd = open((*redir_node)->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!fd)
		return ; // TODO: exit_error ?
	while (1)
	{
		line = get_next_line(0);
		if (ft_strcmp(line, (*redir_node)->delimiter) == 0)
		{
			free(line);
			close(fd);
			return;
		}
		handle_expand(line, data);
		ft_putstr_fd(line, fd);
		free(line);
	}
}
