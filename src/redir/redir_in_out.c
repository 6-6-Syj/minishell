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
◆ Librairies à inclure:
●  #include <unistd.h>
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

void	open_outfile(t_command *cmd, t_data *data)
{
	t_redir	*file;
	int		flags;
	int		new_fd_out;

	file = cmd->redir;
	while (file)
	{
		if (file->type == REDIR_OUT || file->type == REDIR_APPEND)
		{
			if (file->type == REDIR_OUT)
				flags = (O_CREAT | O_TRUNC | O_RDWR);
			else
				flags = (O_CREAT | O_APPEND | O_RDWR);
			// NEED TO CHECK ACCESS !
			new_fd_out = open(file->filename, flags, 0644);
			if (new_fd_out == -1)
				exit_error(data); // TODO: CHECK
			cmd->fd_out = new_fd_out;
		}
		file = file->next;
	}
}

void	open_infile(t_command *cmd, t_data *data)
{
	t_redir	*file;
	int		new_fd_in;

	file = cmd->redir;
	while (file)
	{
		if (file->type == REDIR_IN)
		{
			// NEED TO CHECK ACCESS !
			new_fd_in = open(file->filename, O_RDONLY, 0644);
			if (new_fd_in == -1)
				exit_error(data); // TODO: CHECK
			cmd->fd_in = new_fd_in;
		}
		file = file->next;
	}
}
