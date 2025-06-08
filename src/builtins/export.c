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

static bool	search_key_update_value(t_data *data, t_env **head, char *key,
		char *value)
{
	t_env	*curr;

	curr = *head;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (value)
			{
				free(curr->value);
				curr->value = ft_strdup(value);
				if (!curr->value)
					exit_error(data);
			}
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

static bool	add_key(t_data *data, t_env **head, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit_error(data);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		exit_error(data);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			exit_error(data);
		}
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
	if (search_key_update_value(data, env_lst, key, value) || add_key(data,
			env_lst, key, value))
	{
		upload_env_tab(data);
		return (NO_ERROR);
	}
	return (1);
}
// 1 failure: Some rare cases.	ex:
// not enough memory or fd is full

// TODO: if variable got a value "with spaces",
// there are problems. (PARSING EXPORT)
// It exports at each ' ';
// See raw 110
int	handle_export(t_command *cmd, t_env **env_lst, t_data *data)
{
	int	i;

	i = 1;
	if (cmd && !cmd->args[1])
		data->err = print_export(*env_lst, data);
	else
	{
		while (cmd->args[i])
			data->err = ft_export(env_lst, data, cmd->args[i++]);
	}
	return (data->err);
}
