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

static void	free_env_lst(t_env *copy_env_lst)
{
	t_env	*tmp;

	while (copy_env_lst)
	{
		tmp = copy_env_lst->next;
		free(copy_env_lst->key); // TODO: if()
		free(copy_env_lst->value);
		free(copy_env_lst);
		copy_env_lst = tmp;
	}
}

static int	swap_nodes(t_env *current)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = NULL;
	tmp_value = NULL;
	tmp_key = current->key;
	current->key = current->next->key;
	current->next->key = tmp_key;
	tmp_value = current->value;
	current->value = current->next->value;
	current->next->value = tmp_value;
	return (1);
}

static void	sort_env_list(t_env *env_lst)
{
	t_env	*current;
	t_env	*last;
	int		swapped;

	swapped = 1;
	last = NULL;
	while (swapped)
	{
		swapped = 0;
		current = env_lst;
		while (current && current->next != last)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
				swapped = swap_nodes(current);
			current = current->next;
		}
		last = current;
	}
}

static t_env	*copy_env_list(t_env *env_lst)
{
	t_env	*new;

	if (!env_lst)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL); // TODO: MALLOC ERROR
	new->key = ft_strdup(env_lst->key);
	if (!new->key)
		return (NULL); // TODO: MALLOC ERROR
	if (env_lst->value)
	{
		new->value = ft_strdup(env_lst->value);
		if (!new->value)
		{
			free(new->value);
			return (NULL); // TODO: MALLOC ERROR
		}
	}
	else
		new->value = NULL;
	new->next = copy_env_list(env_lst->next);
	return (new);
}

int	print_export(t_env *env_lst)
{
	t_env	*copy;
	t_env	*current;

	copy = copy_env_list(env_lst);
	if (!copy)
		return (1); // TODO: MALLOC ERROR
	sort_env_list(copy);
	current = copy;
	while (current)
	{
		if (current->value)
			ft_printf("export %s=\"%s\"\n", current->key, current->value);
		else
			ft_printf("export %s\n", current->key);
		current = current->next;
	}
	free_env_lst(copy);
	return (0);
}
