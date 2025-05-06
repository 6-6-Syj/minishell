/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:22:44 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:13:52 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void free_split(char **split)
{
	int i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static bool search_key_update_value(t_env **head, char *key, char *value)
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
			}
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

static bool	add_key(t_env **head, char *key, char *value)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (false); // TODO: ERROR MALLOC
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (false); // TODO: ERROR MALLOC
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
		}
	}
	else
		new->value = NULL;
	new->next = *head;
	*head = new;
	return (true);
}

int	ft_export(t_env **env_lst, char **args, int i)
{
	char *key;
	char *value;
	char *equal;

	key = args[i];
	value = NULL;
	equal = ft_strchr(key, '=');
	if (equal)
	{
		*equal = '\0'; // cut "key" at '='
		value = equal + 1; // start "value" after '='
	}
	if (search_key_update_value(env_lst, key, value))
		return (NO_ERROR);
	if (add_key(env_lst, key, value))
		return (NO_ERROR);
	return (1);
}
// 1 failure: Some rare cases.	ex:
// not enough memory or fd is full

int	handle_export(t_env **env_lst, char *input)
{
	char	**args;
	int		i;
	int		res;

	ft_printf("HOLA\n");
	res = 0;
	i = 1;
	args = ft_split(input, ' ');
	if (!args)
		return (1); // TODO: ERROR MALLOC
	if (!args[1])
	{
		// TODO: print_env sorted...
		free_split(args);
		return (NO_ERROR);
	}
	while (args[i])
	{
		res |= ft_export(env_lst, args, i);
		i++;
	}
	free_split(args);
	return (res);
}
