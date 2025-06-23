/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-21 19:27:38 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-21 19:27:38 by jmagand          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "redir.h"
#include "token.h"
#include <fcntl.h>

/*

ACCESS: int access(const char *pathname, int mode);

	◆  La  fonction  vérifie  si  le  le  path  en  fonction  du/des  mode(s)  sélectionnés
	renseigne en paramètres est valides.
◆  Valeur de mode:
	●  R_OK : Lecture.
	●  W_OK : Ecriture.
	●  X_OK : Exécution.
	●  F_OK : Existence.
◆  Retour: La fonction renvoie 0 si les permissions demandées sont disponibles
ou -1 si l'accès est refusé ou si une erreur survient.

*/

// TODO: CHECK ACCESS ?
static void	open_outfile(t_redir *file, int *fd, t_command *cmd, t_data *data)
{
	int	flags;

	if (file->type == REDIR_OUT || file->type == REDIR_APPEND)
	{
		if (file->type == REDIR_OUT)
			flags = (O_CREAT | O_TRUNC | O_RDWR);
		else
			flags = (O_CREAT | O_APPEND | O_RDWR);
		*fd = open(file->filename, flags, 0644);
		if (*fd == -1)
		{
			perror(file->filename);
			if (data)
				data->err = 1;
		}
		cmd->fd_out = *fd;
	}
}

static void	open_infile(t_redir *file, int *fd, t_command *cmd, t_data *data)
{
	if (file->type == REDIR_IN)
	{
		*fd = open(file->filename, O_RDONLY, 0644);
		if (*fd == -1)
		{
			perror(file->filename);
			if (data)
				data->err = 1;
		}
		cmd->fd_in = *fd;
	}
}

void	open_files(t_command *cmd, t_data *data)
{
	t_redir	*file;
	int		new_fd_out;
	int		new_fd_in;

	file = cmd->redir;
	while (file)
	{
		open_infile(file, &new_fd_in, cmd, data);
		open_outfile(file, &new_fd_out, cmd, data);
		if (!data->err)
			file = file->next;
		else
			break ;
	}
	redir(cmd, data);
}

void	free_pid_list(t_pid_list *pids)
{
	t_pid_list	*tmp;

	while (pids)
	{
		tmp = pids;
		pids = pids->next;
		free(tmp);
	}
}

static t_command	*find_last_cmd(t_ast *node)
{
	if (!node)
		return (NULL);
	if (node->type == CMD)
		return (&node->command);
	if (node->type == PIPE)
		return (find_last_cmd(node->pipe.right));
	return (NULL);
}

bool	is_last_command_in_ast(t_command *cmd, t_ast *root)
{
	t_command	*rightmost;

	rightmost = find_last_cmd(root);
	return (rightmost == cmd);
}
