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
#include "data.h"
#include "libft.h"
#include <errno.h>
#include <linux/limits.h>

static int	w_getcwd(char *path, t_data *data)
{
	if (!getcwd(path, PATH_MAX))
		data->err = 1;
	else
		data->err = 0;
	return (data->err);
}

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
			ft_putendl_fd("No such file or directory", STDERR_FILENO);
		else if (errno == EACCES)
			ft_putendl_fd("Permission denied", STDERR_FILENO);
		else
			ft_putendl_fd("Cannot access directory", STDERR_FILENO);
	}
	else
		ft_putendl_fd(path, STDOUT_FILENO);
	return (data->err);
}
