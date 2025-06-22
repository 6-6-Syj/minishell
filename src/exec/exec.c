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

// static int	handle_and_or(t_ast *node, t_data *data)
// {
// 	ret = handle_ast(node->logic.left, data);
// 	if (node->type == AND)
// 	{
// 		if (ret == 0)
// 			ret = handle_ast(node->logic.right, data);
// 	}
// 	else // type == OR
// 	{
// 		if (ret != 0)
// 			ret = handle_ast(node->logic.right, data);
// 	}
// 	return (ret);
// }

void	handle_ast(t_ast *node, t_data *data, int *fd)
{
	if (!node)
		return ;
	// if (node && node->type == CMD)
	// {
	// 	ft_printf("┌───────── Command Info ────────┐\n");
	// 	ft_printf("│\tCommand: %s\t\t│\n", node->command.args[0]);
	// 	ft_printf("│\tInput FD: %d\t\t│\n", node->command.fd_in);
	// 	ft_printf("│\tOutput FD: %d\t\t│\n", node->command.fd_out);
	// 	ft_printf("└───────────────────────────────┘\n");
	// }
	// else if (node && (node->type == AND || node->type == OR))
	// 	handle_and_or(node, data);
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

// Version corrigée de exec_ast
void exec_ast(t_ast *node, t_data *data)
{
    int fd[2];
    t_fd_backup backup = {-1, -1, -1}; // Initialisation explicite

    fd[0] = -1;
    fd[1] = -1;
    if (!node)
        exit_error(data);
    if (node->type == CMD && node->command.args && node->command.args[0] &&
        is_builtin(node->command.args[0]))
    {
        if (backup_fds(&backup) == -1)
        {
			// TODO: CHECK -> if DUP FAILS - printf smtg ?
            exit_error(data);
        }
        open_infile(&node->command, data);
        open_outfile(&node->command, data);
        redir(&node->command, data);
        data->err = exec_builtin(&node->command, &data->env, data);
        restore_fds(&backup, data);
        unset_redirect_fds(&node->command);
		close_inherited_fds(&node->command);
    }
    else
    {
        handle_ast(node, data, fd);
        wait_process();
    }
}

// void	exec_ast(t_ast *node, t_data *data)
// {
// 	int	fd[2];

// 	fd[0] = -1;
// 	fd[1] = -1;
// 	if (!node)
// 		exit_error(data); // TODO: CHECK ERROR
// 	if (node->type == CMD && is_builtin(node->command.args[0]))
// 	{
// 		open_infile(&node->command, data);
// 		open_outfile(&node->command, data);
// 		ft_printf("&fd[0] = %x | &fd[1] = %x\n", &fd[0], &fd[1]);
// 		redir_builtin_solo(&fd[0], &fd[1], data);
// 		close_inherited_fds(&node->command);
// 		data->err = exec_builtin(&node->command, &data->env, data);
// 	}
// 	else
// 	{
// 		handle_ast(node, data, fd);
// 		wait_process();
// 	}
// }
