/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:33:10 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/02 19:16:29 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wrappers.h"
#include "libft.h"
#include "data.h"
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	w_execve(char *path, char **cmds, char **env, t_data *data)
{
	w_signal(SIGINT, SIG_DFL, data);
	w_signal(SIGQUIT, SIG_DFL, data);
	if (execve(path, cmds, env) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
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
		perror("minishell: close");
		if (data)
			data->err = errno;
		exit_error(data);
	}
}
