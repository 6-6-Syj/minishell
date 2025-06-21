/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-21 14:32:55 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-21 14:32:55 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

> : Redirection de sortie (écrase le fichier)

	Redirige la sortie standard (stdout) d'une commande vers un fichier,
	en écrasant son contenu s'il existe.

	echo "Bonjour" > fichier.txt

	Si fichier.txt n'existe pas, il est créé.
	S'il existe, son contenu est remplacé par "Bonjour".

*/

#include "command.h"
#include "redir.h"
#include "token.h"
#include <fcntl.h>

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
			new_fd_out = open(file->filename, flags, 0644);
			if (new_fd_out == -1)
				exit_error(data); // TODO: CHECK
			cmd->fd_out = new_fd_out;
		}
		file = file->next;
	}
}
