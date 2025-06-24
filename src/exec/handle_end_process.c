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

static void	handle_normal(pid_t wpid, int status, t_wait_data *wait_data)
{
	t_pid_list	*current;

	ft_printf("Child PID %d ended normally with status %d", wpid,
		WEXITSTATUS(status));
	current = wait_data->pids;
	while (current)
	{
		if (current->pid == wpid && current->is_last_cmd)
		{
			*(wait_data->last_exit_code) = WEXITSTATUS(status);
			wait_data->data->err = *(wait_data->last_exit_code);
			wait_data->data->exit_err = *(wait_data->last_exit_code);
		}
		current = current->next;
	}
}

static void	handle_signal(pid_t wpid, int status, t_wait_data *wait_data)
{
	t_pid_list	*current;

	ft_printf("Child PID %d was killed by signal %d", wpid, WTERMSIG(status));
	current = wait_data->pids;
	while (current)
	{
		if (current->pid == wpid && current->is_last_cmd)
		{
			*(wait_data->last_exit_code) = 128 + WTERMSIG(status);
			wait_data->data->err = *(wait_data->last_exit_code);
		}
		current = current->next;
	}
}

void	handle_end_process(pid_t wpid, int status, t_wait_data *wait_data)
{
	ft_printf("\033[0;32m\033[1m");
	if (WIFEXITED(status))
		handle_normal(wpid, status, wait_data);
	else if (WIFSIGNALED(status))
		handle_signal(wpid, status, wait_data);
	else /* TODO: NEED FIX ELSE */
		ft_printf("OUPS\n");
	ft_printf("\033[0m");
}
