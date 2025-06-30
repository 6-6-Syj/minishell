/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:36:22 by jmagand           #+#    #+#             */
/*   Updated: 2025/06/26 23:45:18 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "pipe.h"
#include "redir.h"
#include <errno.h>
#include <string.h>

void	handle_ast(t_ast *node, t_data *data, int *fd, t_pid_list **pids)
{
	if (!node)
		return ;
	if (node->type == CMD)
		handle_command(&node->command, data, pids, node);
	else if (node->type == PIPE)
		handle_pipe(&node->pipe, data, fd, pids);
}

static int	wait_all_processes(t_pid_list *pids, t_data *data)
{
	int			status;
	int			last_exit_code;
	t_pid_list	*current;

	last_exit_code = 0;
	current = pids;
	while (current)
	{
		if (waitpid(current->pid, &status, 0) > 0)
		{
			if (current->is_last_cmd)
			{
				last_exit_code = get_exit_code(status);
				data->err = last_exit_code;
				data->exit_err = last_exit_code;
				log_process_end(current->pid, status);
			}
		}
		else
			log_process_end(current->pid, status);
		current = current->next;
	}
	return (last_exit_code);
}

static void	init_backup(t_fd_backup *backup)
{
	backup->fd_in = -1;
	backup->fd_out = -1;
	backup->fd_err = -1;
}

void	exec_and_restore_fd(t_fd_backup *backup, t_command *cmd, t_data *data)
{
	data->err = exec_builtin(cmd, &data->env, data);
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
		exit_error(data);
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
		data->err = wait_all_processes(pids, data);
		free_pid_list(pids);
	}
}
