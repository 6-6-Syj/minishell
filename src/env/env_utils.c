/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 21:18:49 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-21 21:18:49 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_env_tab(char **env_tab)
{
	int	i;

	if (!env_tab)
	{
		ft_printf("NULL.\n");
		return ;
	}
	i = 0;
	while (env_tab[i])
	{
		ft_printf("%s\n", env_tab[i]);
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

char	**upload_env_tab(t_data *data)
{
	int		size;
	int		i;
	char	*buff;
	t_env	*env_node;

	i = 0;
	size = get_size_env_lst(data->env);
	data->env_tab = malloc(sizeof(char *) * (size + 1));
	env_node = data->env;
	if (!data->env_tab)
		return (NULL); // TODO: MALLOC ERROR
	while (env_node)
	{
		buff = ft_strjoin(env_node->key, "=");
		if (!buff)
			return (NULL); // TODO: MALLOC ERROR
		data->env_tab[i] = ft_strjoin(buff, env_node->value);
		if (!data->env_tab[i])
			return (NULL); // TODO: MALLOC ERROR
		if (buff)
			free(buff);
		i++;
		env_node = env_node->next;
	}
	data->env_tab[i] = NULL;
	return (data->env_tab);
}
