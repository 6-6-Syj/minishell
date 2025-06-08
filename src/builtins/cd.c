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
#include "errno.h"
#include "libft.h"

static int	w_chdir(char *path, t_data *data)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
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
	return (0);
}

static int	cd_oldpwd(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(current->key, "OLDPWD"))
		{
			if (w_chdir(current->value, data) == 0)
			{
				ft_putstr_fd(current->value, STDIN_FILENO);
				ft_putstr_fd("\n", STDIN_FILENO);
			}
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
			return (w_chdir(current->value, data));
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
	return (w_chdir(cmd->args[1], data));
}
