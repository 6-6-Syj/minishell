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

void	clean_all_processes(t_pid_list *pids)
{
	t_pid_list	*current;
	int			status;

	current = pids;
	while (current)
	{
		if (!current->is_last_cmd)
		{
			if (waitpid(current->pid, &status, 0) > 0)
				log_process_end(current->pid, status);
		}
		current = current->next;
	}
}

int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

void	log_process_end(pid_t wpid, int status)
{
	ft_printf("\033[0;32m\033[1m");
	if (WIFEXITED(status))
		ft_printf("Child PID %d ended normally with status %d", wpid,
			WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_printf("Child PID %d was killed by signal %d", wpid,
			WTERMSIG(status));
	else
		ft_printf("Child PID %d ended with unknown status", wpid);
	ft_printf("\033[0m");
}
