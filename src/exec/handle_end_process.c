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
		ft_printf("Child PID %d ended normally with status %d\n", wpid,
			WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_printf("Child PID %d was killed by signal %d\n", wpid,
			WTERMSIG(status));
	else
		ft_printf("Child PID %d ended with unknown status\n", wpid);
	ft_printf("\033[0m");
}
