/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:04 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:50:38 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

/*
	ERRORS FROM CHDIR:

	● EACCES (13): Permission denied to access the specified directory.

	● ENOENT (2): The specified directory does not exist.

	● ENOTDIR (20): Part of the specified path is not a directory.
*/

static void	error_message(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

static int	cd_oldpwd(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(current->key, "OLDPWD"))
		{
			if (chdir(current->value) == -1)
			{
				error_message(current->value);
				data->err = 1;
			}
			else
				data->err = 0;
			return (data->err);
		}
		current = current->next;
	}
	ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	data->err = 1;
	return (data->err);
}

static int	cd_home(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(current->key, "HOME"))
		{
			if (chdir(current->value) == -1)
			{
				error_message(current->value);
				data->err = 1;
			}
			else
				data->err = 0;
			return (data->err);
		}
		current = current->next;
	}
	ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	data->err = 1;
	return (data->err);
}

int	ft_cd(t_command *cmd, t_data *data)
{
	int	i;

	i = 1;
	while (cmd && cmd->args[i])
		i++;
	if (i == 1)
		return (cd_home(data));
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	if (!ft_strcmp(cmd->args[1], "-"))
		return (cd_oldpwd(data));
	if (chdir(cmd->args[1]) == -1)
	{
		error_message(cmd->args[1]);
		data->err = 1;
		return (data->err);
	}
	data->err = 0;
	return (0);
}
