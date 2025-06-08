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

/*
TODO: CHECK ERROR MESSAGES

bash-5.1$ cd salut/
bash-5.1$ pwd
pwd: error retrieving current directory: getcwd: cannot access parent
			directories: No such file or directory
bash-5.1$ mkdir salut
mkdir: cannot create directory ‘salut’: No such file or directory
bash-5.1$ cd
chdir: error retrieving current directory: getcwd: cannot access parent
			directories: No such file or directory
bash-5.1$ exit
*/

static int	w_getcwd(char *path, t_data *data)
{
	if (!getcwd(path, PATH_MAX))
	{
		ft_putstr_fd("getcwd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		else if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (errno == ENOTDIR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Cannot access directory\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	data->err = 0;
	return (data->err);
}

int	ft_pwd(t_data *data)
{
	char	res[PATH_MAX];

	if (!w_getcwd(res, data))
	{
		ft_putstr_fd(res, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (data->err);
}
