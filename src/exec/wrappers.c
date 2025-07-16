/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 15:33:10 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-23 15:33:10 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrappers.h"
#include "redir.h"
#include <errno.h>

void	w_execve(char *path, char **cmds, char **env, t_data *data)
{
	if (execve(path, cmds, env) == -1)
	{
		perror(path);
		free(path);
		if (data)
			data->err = errno;
		exit_error(data);
	}
}

void	w_close(int fd, t_data *data)
{
	if (close(fd) == -1)
	{
		perror("close");
		if (data)
			data->err = errno;
		exit_error(data);
	}
}
