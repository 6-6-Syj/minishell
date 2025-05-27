/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 19:01:46 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-27 19:01:46 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	redir_in(t_command *cmd, t_data *data)
{
	if (cmd && cmd->fd_in > 0 && cmd->fd_in != STDIN_FILENO)
	{
		w_dup2(cmd->fd_in, STDIN_FILENO, data);
		w_close(cmd->fd_in, data);
	}
}

void	redir_out(t_command *cmd, t_data *data)
{
	if (cmd && cmd->fd_out > 1 && cmd->fd_out != STDOUT_FILENO)
	{
		w_dup2(cmd->fd_out, STDOUT_FILENO, data);
		w_close(cmd->fd_out, data);
	}
}
