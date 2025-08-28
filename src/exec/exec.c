/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:36:22 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/26 16:48:18 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "handle_signal.h"
#include "pipe.h"
#include "redir.h"

/*
		void	handle_command(t_command *cmd, t_data *data, t_pid_list **pids,
				t_ast *root)
		{
			pid_t	pid;
			bool	is_last;

			pid = w_fork(data);
			if (pid == 0)
			{
				data->pid_list = NULL;
				if (pids && *pids)
				{
					free_pid_list(pids);
					*pids = NULL;
				}
				open_files(cmd, data);
				close_inherited_fds(cmd);
				if (!data->err)
					exec_command(cmd, data);
				else
					exit_error(data);
			}
			else
			{
				is_last = is_last_command_in_ast(root);
				add_pid(pids, pid, is_last, data);
				if (cmd->fd_in > 2)
					w_close(cmd->fd_in, data);
				if (cmd->fd_out > 2)
					w_close(cmd->fd_out, data);
			}
		}
*/

void	handle_ast(t_ast *node, t_data *data, int *fd, t_pid_list **pids)
{
	if (!node)
		return ;
	if (node->type == CMD && (node->command.args[0] || node->command.redir))
		handle_command(&node->command, data, pids, node);
	else if (node->type == PIPE)
		handle_pipe(&node->pipe, data, fd, pids);
}

static void	init_backup(t_fd_backup *backup)
{
	backup->fd_in = -1;
	backup->fd_out = -1;
	backup->fd_err = -1;
}

static bool	is_echo_exit_status(t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return (false);
	if (!cmd->args[0] || ft_strcmp(cmd->args[0], "echo") != 0)
		return (false);
	i = 1;
	while (cmd->args[i])
	{
		if (!ft_strcmp(cmd->args[i], "$?"))
			return (true);
		i++;
	}
	return (false);
}

void	exec_and_restore_fd(t_fd_backup *backup, t_command *cmd, t_data *data)
{
	if (is_echo_exit_status(cmd))
		exec_builtin(cmd, &data->env, data);
	else
		data->err = exec_builtin(cmd, &data->env, data);
	data->exit_err = data->err;
	restore_fds(backup, data);
	unset_redirect_fds(cmd);
	close_inherited_fds(cmd);
}

void	exec_ast(t_ast *node, t_data *data)
{
	int			fd[2];
	t_fd_backup	backup;
	t_pid_list	*pids;

	pids = NULL;
	fd[0] = 0;
	fd[1] = 1;
	init_backup(&backup);
	if (!node)
		return ;
	if (node->type == CMD && node->command.args && node->command.args[0]
		&& is_builtin(node->command.args[0]))
	{
		if (backup_fds(&backup) == -1)
			exit_error(data);
		open_files(&node->command, data);
		if (!data->err)
			exec_and_restore_fd(&backup, &node->command, data);
	}
	else
	{
		handle_ast(node, data, fd, &pids);
		if (!data->err)
			data->err = wait_all_processes(pids, data);
	}
}
