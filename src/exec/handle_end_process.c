/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:39:56 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/04 19:00:21 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "handle_signal.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	get_exit_code(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		if (sig == SIGPIPE)
			return (0);
		else
			return (128 + sig);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	wait_all_processes(t_data *data)
{
	int		status;
	int		last_exit_code;
	int		w_pid;
	
	last_exit_code = 0;
	w_pid = 1;
	while (w_pid > 0)
	{
		w_pid = waitpid(-1, &status, 0);		
		if (w_pid == data->last_cmd_pid)
		{
			signal(SIGINT, SIG_IGN);
			last_exit_code = get_exit_code(status);
			signal(SIGINT, sig_handler);
			data->err = last_exit_code;
			data->exit_err = last_exit_code;
		}
	}
	return (last_exit_code);
}
