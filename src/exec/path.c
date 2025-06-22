/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 15:38:43 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-23 15:38:43 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "exec.h"

void	*free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (NULL);
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

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
				exit_error(data);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static int	is_absolute_or_relative_path(char *cmd)
{
	return (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd,
			"../", 3) == 0);
}

char	*get_path(char *cmd, t_data *data)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !data)
		return (NULL);
	if (is_absolute_or_relative_path(cmd))
		return (ft_strdup(cmd));
	paths = split_path(data);
	if (!paths)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (full_path && access(full_path, F_OK) == 0)
		{
			free_strs(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_strs(paths);
	return (NULL);
}
