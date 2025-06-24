/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:37:23 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:14:55 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <errno.h>
#include <stdio.h>

static int	w_getcwd(char *path, t_data *data)
{
	if (!getcwd(path, PATH_MAX))
		data->err = 1;
	else
		data->err = 0;
	return (data->err);
}

/* TODO: CHECK ERROR MESSAGES */
int	ft_pwd(t_data *data)
{
	char	path[PATH_MAX];

	ft_bzero(path, PATH_MAX);
	if (w_getcwd(path, data))
	{
		ft_putstr_fd("pwd: error retrieving current directory: ",
			STDERR_FILENO);
		ft_putstr_fd("getcwd: cannot access parent directories: ",
			STDERR_FILENO);
		if (errno == ENOENT)
			ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		else if (errno == EACCES)
			ft_putstr_fd("Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd("Cannot access directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (data->err);
}
