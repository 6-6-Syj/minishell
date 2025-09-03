/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:22:44 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:26:21 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "libft.h"
#include "data.h"

static bool	search_key_update_value(t_data *data, char *key, char *value)
{
	t_env	*curr;

	curr = data->env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (value)
			{
				free(curr->value);
				curr->value = ft_strdup(value);
				if (!curr->value)
					malloc_fail(data);
			}
			curr->print_env = true;
			curr->print_exp = true;
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

static void	free_and_exit(t_data *data, t_env *new)
{
	free(new->key);
	free(new);
	malloc_fail(data);
}

static bool	add_key(t_data *data, t_env **head, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		malloc_fail(data);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		malloc_fail(data);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			free_and_exit(data, new);
	}
	else
		new->value = NULL;
	new->next = *head;
	*head = new;
	return (true);
}

static int	ft_export(t_env **env_lst, t_data *data, char *args)
{
	char	*key;
	char	*value;
	char	*equal;

	key = args;
	value = NULL;
	equal = ft_strchr(key, '=');
	if (equal)
	{
		*equal = '\0';
		value = equal + 1;
	}
	if (!is_key_valid(key))
		return (1);
	if (got_special_char(key))
		return (2);
	if (search_key_update_value(data, key, value) || add_key(data, env_lst, key,
			value))
	{
		update_env_tab(data);
		return (0);
	}
	return (1);
}

int	handle_export(t_command *cmd, t_env **env_lst, t_data *data)
{
	int	i;

	i = 1;
	if (cmd && !cmd->args[1])
		data->err = print_export(*env_lst, data);
	else
	{
		while (cmd->args[i])
		{
			data->err = ft_export(env_lst, data, cmd->args[i]);
			i++;
		}
	}
	return (data->err);
}
