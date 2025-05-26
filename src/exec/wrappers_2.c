/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 16:14:43 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-23 16:14:43 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"
# include "data.h"
# include <errno.h>

void	w_pipe(int *fd, t_data *data)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		if (data)
			data->err = errno;
		exit_error(data);
	}
}

void	w_dup2(int old, int new, t_data *data)
{
	if (dup2(old, new) == -1)
	{
		perror("dup2");
		if (data)
			data->err = errno;
		exit_error(data);
	}
}

int	w_fork(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (data)
			data->err = errno;
		exit_error(data);
	}
	return (pid);
}

void	redir_out(t_data *data, int *fd)
{
	if (fd[0] != -1)
		w_close(fd[0], data); // Close read (useless fd)
	w_dup2(fd[1], STDOUT_FILENO, data);
	w_close(fd[1], data); // Close old writing fd
}

void	redir_in(t_data *data, int *fd)
{
	if (fd[1] != -1)
		w_close(fd[1], data); // Close write (useless fd)
	w_dup2(fd[0], STDIN_FILENO, data);
	w_close(fd[0], data); // Close old reading fd
}
