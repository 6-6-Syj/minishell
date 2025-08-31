/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:38:43 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/22 22:28:40 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "data.h"
#include "exec.h"
#include "utils.h"

static char	*build_full_path(char *dir, char *cmd)
{
	char	*slash_cmd;
	char	*full_path;

	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	full_path = ft_strjoin(dir, slash_cmd);
	free(slash_cmd);
	return (full_path);
}

static char	**split_path(t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	if (!data || !data->env_tab)
		return (NULL);
	while (data->env_tab[i])
	{
		if (ft_strncmp("PATH=", data->env_tab[i], 5) == 0)
		{
			paths = ft_split(data->env_tab[i] + 5, ':');
			if (!paths)
				malloc_fail(data);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (full_path && access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*find_cmd_in_path(char *cmd, t_data *data, t_path_status *status)
{
	char	**paths;
	char	*result;

	paths = split_path(data);
	if (!paths)
	{
		*status = PATH_UNSET;
		return (NULL);
	}
	result = find_path(paths, cmd);
	free_strs(paths);
	if (result)
		*status = PATH_OK;
	else
		*status = PATH_NOT_FOUND;
	return (result);
}

char	*resolve_command_path(char *cmd, t_data *data, t_path_status *status)
{
	char	*result;

	if (!cmd || !data || !cmd[0])
	{
		*status = PATH_NOT_FOUND;
		return (NULL);
	}
	if (is_absolute_or_relative_path(cmd))
	{
		result = ft_strdup(cmd);
		if (!result)
			malloc_fail(data);
		*status = PATH_OK;
		return (result);
	}
	return (find_cmd_in_path(cmd, data, status));
}
