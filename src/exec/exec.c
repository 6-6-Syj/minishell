/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 18:36:22 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-09 18:36:22 by jmagand          ###   ########.fr       */
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

/*

WIFSIGNALED(status) : Vrai si le processus fils a été terminé par un signal.

WTERMSIG(status) : Si WIFSIGNALED est vrai,
	retourne le numéro du signal qui a tué le processus.

WIFSTOPPED(status) : Vrai si le processus fils a été stoppé (par exemple,
	par SIGSTOP).

WSTOPSIG(status) : Si WIFSTOPPED est vrai,
	retourne le numéro du signal qui a stoppé le processus.

 */

static void	clean_all_processes(t_pid_list *pids, t_wait_data *wait_data)
{
	t_pid_list	*current;
	int			status;

	current = pids;
	while (current)
	{
		if (!current->is_last_cmd)
			if (waitpid(current->pid, &status, 0) > 0)
				handle_end_process(current->pid, status, wait_data);
		current = current->next;
	}
}

static int	wait_all_processes(t_pid_list *pids, t_data *data)
{
	int			status;
	int			last_exit_code;
	t_pid_list	*current;
	t_wait_data	wait_data;

	last_exit_code = 0;
	wait_data.pids = pids;
	wait_data.data = data;
	wait_data.last_exit_code = &last_exit_code;
	current = pids;
	while (current)
	{
		if (current->is_last_cmd)
		{
			if (waitpid(current->pid, &status, 0) > 0)
				handle_end_process(current->pid, status, &wait_data);
			break ;
		}
		current = current->next;
	}
	clean_all_processes(pids, &wait_data);
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
	fd[0] = -1;
	fd[1] = -1;
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
