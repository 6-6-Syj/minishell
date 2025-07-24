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
#include "signal.h"

/*

WIFSIGNALED(status) : Vrai si le processus fils a été terminé par un signal.

WTERMSIG(status) : Si WIFSIGNALED est vrai,
	retourne le numéro du signal qui a tué le processus.

WIFSTOPPED(status) : Vrai si le processus fils a été stoppé (par exemple,
	par SIGSTOP).

WSTOPSIG(status) : Si WIFSTOPPED est vrai,
	retourne le numéro du signal qui a stoppé le processus.

*/

int	get_exit_code(int status, t_data *data)
{
	int	sig;

	signal(SIGINT, SIG_IGN);
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
			write(STDERR_FILENO, "Quit minishell(core dumped)\n", 28);
		}
		signal(SIGINT, sig_handler);
		return (128 + sig);
	}
	else if (WIFEXITED(status))
	{
		signal(SIGINT, sig_handler);
		return (WEXITSTATUS(status));
	}
	signal(SIGINT, sig_handler);
	return (1);
}
