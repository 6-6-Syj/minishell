/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:46 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/08 18:34:52 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	redir(t_command *cmd, t_data *data)
{
	if (cmd && cmd->fd_in > 0 && cmd->fd_in != STDIN_FILENO)
	{
		w_dup2(cmd->fd_in, STDIN_FILENO, data);
		w_close(cmd->fd_in, data);
	}
	if (cmd && cmd->fd_out > 1 && cmd->fd_out != STDOUT_FILENO)
	{
		w_dup2(cmd->fd_out, STDOUT_FILENO, data);
		w_close(cmd->fd_out, data);
	}
}

void	redir_builtin_solo(int *fd_in, int *fd_out, t_data *data)
{
	if (*fd_in > 0 && *fd_in != STDIN_FILENO)
	{
		w_dup2(*fd_in, STDIN_FILENO, data);
		w_close(*fd_in, data);
	}
	if (*fd_out > 1 && *fd_out != STDOUT_FILENO)
	{
		w_dup2(*fd_out, STDOUT_FILENO, data);
		w_close(*fd_out, data);
	}
}
