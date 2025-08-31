/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-24 20:17:38 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-24 20:17:38 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "libft.h"

void	free_copy_env_lst(t_env *copy_env_lst)
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

void	sort_env_list(t_env *env_lst)
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
