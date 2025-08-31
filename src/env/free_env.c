/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:22:13 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/18 22:09:50 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "data.h"

static void	free_lst_node(t_env *env_node)
{
	if (!env_node)
		return ;
	if (env_node->key)
		free(env_node->key);
	if (env_node->value)
		free(env_node->value);
	free(env_node);
}

void	free_env_lst(t_env **env_lst)
{
	t_env	*current;
	t_env	*next;

	if (!env_lst || !*env_lst)
		return ;
	current = *env_lst;
	while (current)
	{
		next = current->next;
		free_lst_node(current);
		current = next;
	}
	*env_lst = NULL;
}

void	free_env_tab(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_tab[i])
	{
		free(data->env_tab[i]);
		i++;
	}
	free(data->env_tab);
	data->env_tab = NULL;
}
