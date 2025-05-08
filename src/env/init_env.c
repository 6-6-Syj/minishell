/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 21:05:29 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-05 21:05:29 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	set_env(t_env *new_env, char *env_line)
{
	char	*equal;

	equal = ft_strchr(env_line, '=');
	if (equal)
	{
		new_env->key = ft_strndup(env_line, equal - env_line);
		new_env->value = ft_strdup(equal + 1);
		new_env->print_env = true;
		new_env->print_exp = true;
	}
}

t_env	*get_last_env(t_env *lst)
{
	t_env	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_env	*add_env_node(t_env *env_lst)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL); // TODO: Malloc error
	if (!env_lst)
	{
		env_lst = new_node;
		new_node->prev = NULL; // NEEDED ?
	}
	else
	{
		last_node = get_last_env(env_lst);
		last_node->next = new_node;
		new_node->prev = last_node; // NEEDED ?
	}
	new_node->next = NULL;
	return (new_node);
}

void	init_env(t_env **env_lst, char **env)
{
	t_env	*new_env;
	int		i;

	*env_lst = NULL;
	i = 0;
	while (env[i])
	{
		new_env = add_env_node(*env_lst);
		if (!new_env)
			return ;
		// TODO: Malloc error ?
		set_env(new_env, env[i]);
		// If *env is still NULL, update it
		if (!*env_lst)
			*env_lst = new_env;
		i++;
	}
}
