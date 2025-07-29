/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-24 20:39:56 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-24 20:39:56 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "handle_signal.h"
#include <signal.h>

/*

WIFSIGNALED(status) : Vrai si le processus fils a été terminé par un signal.

WTERMSIG(status) : Si WIFSIGNALED est vrai,
	retourne le numéro du signal qui a tué le processus.

WIFSTOPPED(status) : Vrai si le processus fils a été stoppé (par exemple,
	par SIGSTOP).

WSTOPSIG(status) : Si WIFSTOPPED est vrai,
	retourne le numéro du signal qui a stoppé le processus.

*/

static int	get_exit_code(int status, t_data *data)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT && !data->is_nl)
		{
			data->is_nl = true;
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (sig == SIGQUIT && !data->is_nl)
		{
			data->is_nl = true;
			write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		}
		return (128 + sig);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	wait_all_processes(t_pid_list *pids, t_data *data)
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
				signal(SIGINT, SIG_IGN);
				last_exit_code = get_exit_code(status, data);
				signal(SIGINT, sig_handler);
				data->err = last_exit_code;
				data->exit_err = last_exit_code;
			}
		}
		current = current->next;
	}
	return (last_exit_code);
}
