/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:11:59 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/18 22:33:24 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "print.h"

char	*get_env_var(t_data *data, char *key)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

static int	update_value(t_data *data, char *key, char *value)
{
	t_env	*current;
	size_t	key_len;

	current = data->env;
	key_len = ft_strlen(key);
	while (current)
	{
		if (current->key && !ft_strncmp(current->key, key, key_len + 1))
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				malloc_fail(data);
			update_env_tab(data);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	set_env_var(t_data *data, char *key, char *value)
{
	t_env	*new_node;

	if (!update_value(data, key, value))
	{
		new_node = add_env_node(&data->env);
		if (!new_node)
			malloc_fail(data);
		new_node->key = ft_strdup(key);
		if (!new_node->key)
		{
			free(new_node);
			malloc_fail(data);
		}
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			free(new_node->key);
			free(new_node);
			malloc_fail(data);
		}
		new_node->print_env = 1;
		new_node->print_exp = 1;
		update_env_tab(data);
	}
	return (1);
}
