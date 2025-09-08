/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:39:56 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/08 19:08:12 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "handle_signal.h"
#include "libft.h"
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
			ft_putchar_fd('\n', STDERR_FILENO);
		else if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
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
	int	status;
	int	last_exit_code;
	int	wpid;

	last_exit_code = 0;
	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid == data->last_cmd_pid)
		{
			signal(SIGINT, SIG_IGN);
			last_exit_code = get_exit_code(status);
			signal(SIGINT, sig_handler);
			data->err = last_exit_code;
			data->exit_err = last_exit_code;
		}
		wpid = waitpid(-1, &status, 0);
	}
	return (last_exit_code);
}
