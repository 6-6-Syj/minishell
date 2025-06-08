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

static char	**split_path(char *cmd, t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	if (!cmd)
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

char	*get_path(char *cmd, t_data *data)
{
	char	*buff;
	char	*path;
	char	**paths;
	int		i;

	paths = split_path(cmd, data);
	i = -1;
	while (paths && paths[++i])
	{
		buff = ft_strjoin("/", cmd);
		if (!buff)
			return (NULL);
		path = ft_strjoin(paths[i], buff);
		free(buff);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
		{
			free_strs(paths);
			return (path);
		}
		free(path);
	}
	free_strs(paths);
	return (ft_strdup(cmd));
}
