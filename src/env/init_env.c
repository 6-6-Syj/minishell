/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:05:29 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:26:05 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

bool	is_set_env(t_env *new_env, char *env_line)
{
	char	*equal;

	new_env->print_env = 0;
	new_env->print_exp = 1;
	new_env->key = NULL;
    new_env->value = NULL;
	equal = ft_strchr(env_line, '=');
	if (equal)
	{
		new_env->key = ft_strndup(env_line, equal - env_line);
		if (!new_env->key)
			return (false);
		new_env->value = ft_strdup(equal + 1);
		if (!new_env->value)
			return (false);
		new_env->print_env = 1;
	}
	return (true);
}

t_env	*get_last_env(t_env *env_lst)
{
	t_env	*last;

	last = env_lst;
	if (!env_lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_env	*add_env_node(t_env **env_lst)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (!*env_lst)
	{
		*env_lst = new_node;
		new_node->prev = NULL; // NEEDED ?
	}
	else
	{
		last_node = get_last_env(*env_lst);
		last_node->next = new_node;
		new_node->prev = last_node; // NEEDED ?
	}
	new_node->next = NULL;
	return (new_node);
}

void	init_env(t_data *data, char **env)
{
	t_env	*new_env;
	int		i;

	i = 0;
	while (env[i])
	{
		new_env = add_env_node(&data->env);
		if (!new_env)
			exit_error(data);
		if (!is_set_env(new_env, env[i]))
			exit_error(data);
		// If *env is still NULL, update it
		if (!data->env)
			data->env = new_env;
		i++;
	}
	update_env_tab(data);
}
