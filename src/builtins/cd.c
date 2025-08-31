/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:04 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/26 21:07:47 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "builtins.h"
#include "errno.h"
#include "libft.h"
#include <string.h>
#include <sys/stat.h>
#include "env.h"
#include "data.h"

static int	w_cd(char *target, t_data *data)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	if (!getcwd(oldpwd, PATH_MAX))
		oldpwd[0] = '\0';
	if (chdir(target) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	if (oldpwd[0] != '\0')
		set_env_var(data, "OLDPWD", oldpwd);
	if (getcwd(newpwd, PATH_MAX))
		set_env_var(data, "PWD", newpwd);
	data->err = 0;
	return (0);
}

static bool	validate_oldpwd(char *oldpwd, t_data *data)
{
	struct stat	sb;

	if (!oldpwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		data->err = 1;
	}
	else if (stat(oldpwd, &sb) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(oldpwd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->err = 1;
	}
	else if (!S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(oldpwd, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		data->err = 1;
	}
	if (data->err)
		return (false);
	return (true);
}

static int	cd_oldpwd(t_data *data)
{
	char	oldpwd_stack[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_env_var(data, "OLDPWD");
	ft_strcpy(oldpwd_stack, oldpwd);
	free(oldpwd);
	if (!validate_oldpwd(oldpwd_stack, data))
		return (data->err);
	if (w_cd(oldpwd_stack, data) == 0)
	{
		pwd = get_env_var(data, "PWD");
		if (pwd)
		{
			ft_putstr_fd(pwd, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		free(pwd);
	}
	return (data->err);
}

static int	cd_home(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(current->key, "HOME"))
			return (w_cd(current->value, data));
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
	return (w_cd(cmd->args[1], data));
}
