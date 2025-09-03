/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:18:49 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/02 18:40:36 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "data.h"

void	print_env_tab(char **env_tab)
{
	int	i;

	i = 0;
	while (env_tab[i])
	{
		ft_putendl_fd(env_tab[i], STDOUT_FILENO);
		i++;
	}
}

static int	get_size_env_lst(t_env *current)
{
	int	size;

	size = 0;
	if (!current)
		return (size);
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

static void	update_key_values(t_data *data, t_env *env_node, int i)
{
	char	*buff;

	while (env_node)
	{
		env_node->print_exp = true;
		buff = ft_strjoin(env_node->key, "=");
		if (!buff)
			malloc_fail(data);
		if (env_node->value)
			data->env_tab[i] = ft_strjoin(buff, env_node->value);
		else
			data->env_tab[i] = ft_strdup(buff);
		free(buff);
		if (!data->env_tab[i++])
			malloc_fail(data);
		env_node->print_env = true;
		env_node = env_node->next;
	}
	data->env_tab[i] = NULL;
}

char	**update_env_tab(t_data *data)
{
	int		size;
	int		i;
	t_env	*env_node;

	i = 0;
	if (data && data->env_tab)
	{
		free_strs(data->env_tab);
		data->env_tab = NULL;
	}
	size = get_size_env_lst(data->env);
	data->env_tab = malloc(sizeof(char *) * (size + 1));
	if (!data->env_tab)
		malloc_fail(data);
	env_node = data->env;
	update_key_values(data, env_node, i);
	return (data->env_tab);
}
