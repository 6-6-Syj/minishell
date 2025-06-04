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

	TODO: cd - Change vers $OLDPWD et l'affiche. Erreur si OLDPWD non défini.
*/

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
				ft_putstr_fd("cd: ", STDERR_FILENO);
				ft_putstr_fd(current->value, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				data->err = 1;
				return (data->err);
			}
			else
			{
				data->err = 0;
				return (NO_ERROR);
			}
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
	if (i > 2 || chdir(cmd->args[1]) == -1)
	{
		if (i > 2)
			ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		else
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		data->err = 1; // TODO: CHECK
		return (1);
	}
	else
	{
		data->err = 0;
		return (NO_ERROR);
	}
}
