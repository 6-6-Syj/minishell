#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <token.h>

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

void	set_here_doc(t_redir **redir_node, t_data *data)
{
	char	*line;
	int	fd;

	// (*redir_node)->filename = get_filename_here_doc("/tmp/here_doc", "0000");
	(*redir_node)->filename = ft_strdup("/tmp/here_doc_test");
	fd = open((*redir_node)->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!fd)
		return ;
		// exit_error(data); ////////
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
