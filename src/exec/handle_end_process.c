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
#include "print.h"
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

void	free_pid_list(t_pid_list **pids_lst)
{
	t_pid_list	*current;
	t_pid_list	*tmp;

	if (!pids_lst || !*pids_lst)
		return ;
	current = *pids_lst;
	while (current && current->prev)
		current = current->prev;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*pids_lst = NULL;
}

static t_pid_list	*get_last_pid(t_pid_list *pid_lst)
{
	t_pid_list	*last;

	last = pid_lst;
	if (!pid_lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	add_pid(t_pid_list **pids, pid_t pid, bool is_last, t_data *data)
{
	t_pid_list	*new_node;
	t_pid_list	*last_node;

	new_node = ft_calloc(1, sizeof(t_pid_list));
	if (!new_node)
		malloc_fail(data);
	if (!(*pids))
	{
		*pids = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last_node = get_last_pid(*pids);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
	new_node->pid = pid;
	new_node->is_last_cmd = is_last;
	data->pid_list = *pids;
}

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
		if (sig == SIGPIPE)
			return (0);
		else
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
