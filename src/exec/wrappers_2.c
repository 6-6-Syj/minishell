/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:14:43 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/26 20:01:47 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "wrappers.h"
#include <errno.h>

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

void	w_dup2(int new, int old, t_data *data)
{
	if (dup2(new, old) == -1)
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
