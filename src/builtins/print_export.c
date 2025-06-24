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

static void	free_copy_env_lst(t_env *copy_env_lst)
{
	t_env	*tmp;

	while (copy_env_lst)
	{
		tmp = copy_env_lst->next;
		if (copy_env_lst->key)
			free(copy_env_lst->key);
		if (copy_env_lst->value)
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

static t_env	*copy_env_list(t_env *env_lst, t_data *data)
{
	t_env	*new;

	if (!env_lst)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		exit_error(data);
	new->key = ft_strdup(env_lst->key);
	if (!new->key)
	{
		free(new);
		exit_error(data);
	}
	if (env_lst->value)
	{
		new->value = ft_strdup(env_lst->value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			exit_error(data);
		}
	}
	else
		new->value = NULL;
	new->next = copy_env_list(env_lst->next, data);
	return (new);
}

int	print_export(t_command *cmd, t_env *env_lst, t_data *data)
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
		if (current->value)
		{
			ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putendl_fd(current->key, STDOUT_FILENO);
		}
		current = current->next;
	}
	free_copy_env_lst(copy);
	return (0);
}
