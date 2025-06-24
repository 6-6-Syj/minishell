/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-22 19:48:12 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-22 19:48:12 by jmagand          ###   ########\         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	backup_fds(t_fd_backup *backup)
{
	if (!backup)
		return (-1);
	backup->fd_in = dup(STDIN_FILENO);
	backup->fd_out = dup(STDOUT_FILENO);
	backup->fd_err = dup(STDERR_FILENO);
	if (backup->fd_in == -1 || backup->fd_out == -1 || backup->fd_err == -1)
	{
		if (backup->fd_in != -1)
			close(backup->fd_in);
		if (backup->fd_out != -1)
			close(backup->fd_out);
		if (backup->fd_err != -1)
			close(backup->fd_err);
		return (-1);
	}
	return (0);
}

void	restore_fds(t_fd_backup *backup, t_data *data)
{
	if (!backup)
		return ;
	if (backup->fd_in != -1)
	{
		w_dup2(backup->fd_in, STDIN_FILENO, data);
		w_close(backup->fd_in, data);
		backup->fd_in = -1;
	}
	if (backup->fd_out != -1)
	{
		w_dup2(backup->fd_out, STDOUT_FILENO, data);
		w_close(backup->fd_out, data);
		backup->fd_out = -1;
	}
	if (backup->fd_err != -1)
	{
		w_dup2(backup->fd_err, STDERR_FILENO, data);
		w_close(backup->fd_err, data);
		backup->fd_err = -1;
	}
}

void	unset_redirect_fds(t_command *cmd)
{
	if (cmd->fd_in > 2)
	{
		close(cmd->fd_in);
		cmd->fd_in = STDIN_FILENO;
	}
	if (cmd->fd_out > 2)
	{
		close(cmd->fd_out);
		cmd->fd_out = STDOUT_FILENO;
	}
}
