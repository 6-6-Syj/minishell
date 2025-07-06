/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:52:29 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:57:56 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "print.h"

static void	free_and_exit(t_env *node, t_data *data)
{
	if (node && node->key)
		free(node->key);
	if (node)
		free(node);
	malloc_fail(data);
}

static t_env	*copy_env_list(t_env *env_lst, t_data *data)
{
	t_env	*node;

	if (!env_lst)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		malloc_fail(data);
	node->key = ft_strdup(env_lst->key);
	if (!node->key)
		free_and_exit(node, data);
	if (env_lst->value)
	{
		node->value = ft_strdup(env_lst->value);
		if (!node->value)
			free_and_exit(node, data);
	}
	else
		node->value = NULL;
	node->print_env = env_lst->print_env;
	node->print_exp = env_lst->print_exp;
	node->next = copy_env_list(env_lst->next, data);
	return (node);
}

static void	print_keys_values(t_env *current)
{
	if (current->print_exp)
	{
		if (current->value)
		{
			if (ft_strcmp(current->key, "_"))
			{
				ft_putstr_fd("export ", STDOUT_FILENO);
				ft_putstr_fd(current->key, STDOUT_FILENO);
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(current->value, STDOUT_FILENO);
				ft_putendl_fd("\"", STDOUT_FILENO);
			}
		}
		else
		{
			if (ft_strcmp(current->key, "_"))
			{
				ft_putstr_fd("export ", STDOUT_FILENO);
				ft_putendl_fd(current->key, STDOUT_FILENO);
			}
		}
	}
}

int	print_export(t_env *env_lst, t_data *data)
{
	t_env	*copy;
	t_env	*current;

	copy = copy_env_list(env_lst, data);
	if (!copy)
		exit_error(data);
	sort_env_list(copy);
	current = copy;
	while (current)
	{
		print_keys_values(current);
		current = current->next;
	}
	free_copy_env_lst(copy);
	return (0);
}
