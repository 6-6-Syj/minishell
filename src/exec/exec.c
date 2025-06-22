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

void	handle_ast(t_ast *node, t_data *data, int *fd)
{
	if (!node)
		return ;
	if (node->type == CMD)
		exec_command(&node->command, data);
	else if (node->type == PIPE)
		handle_pipe(&node->pipe, data, fd);
}

/*

WIFEXITED(status) : Vrai si le processus fils s'est terminé normalement (par exemple,
	avec exit() ou return).

WEXITSTATUS(status) : Si WIFEXITED est vrai,
	retourne le code de sortie du processus fils (la valeur passée à exit() ou return).

WIFSIGNALED(status) : Vrai si le processus fils a été terminé par un signal.

WTERMSIG(status) : Si WIFSIGNALED est vrai,
	retourne le numéro du signal qui a tué le processus.

WIFSTOPPED(status) : Vrai si le processus fils a été stoppé (par exemple,
	par SIGSTOP).

WSTOPSIG(status) : Si WIFSTOPPED est vrai,
	retourne le numéro du signal qui a stoppé le processus.

 */

static void	wait_process(void)
{
	int		status;
	pid_t	wpid;

	while ((wpid = wait(&status)) > 0)
	{
		ft_printf("\033[0;32m\033[1m");
		if (WIFEXITED(status))
			ft_printf("Child PID %d ended normally with status %d\n", wpid,
				WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			ft_printf("Child PID %d was killed by signal %d\n", wpid,
				WTERMSIG(status));
		else
			ft_printf("Child PID %d ended with status %d\n", wpid, status);
		ft_printf("\033[0m");
	}
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
		handle_ast(node, data, fd);
		wait_process();
	}
}
