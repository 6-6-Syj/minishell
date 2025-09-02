/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-31 20:50:43 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-31 20:50:43 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "data.h"
#include "handle_signal.h"

bool	is_set_env(t_env *new_env, char *env_line)
{
	char	*equal;

	new_env->print_env = false;
	new_env->print_exp = true;
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
		new_node->prev = NULL;
	}
	else
	{
		last_node = get_last_env(*env_lst);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
	return (new_node);
}

void	init_env(t_data *data, char **env)
{
	t_env	*new_env;
	int		i;

	i = 0;
	if (!env[0])
		init_env_i(data);
	else
	{
		while (env[i])
		{
			new_env = add_env_node(&data->env);
			if (!new_env)
				malloc_fail(data);
			if (!is_set_env(new_env, env[i]))
				malloc_fail(data);
			if (!data->env)
				data->env = new_env;
			i++;
		}
	}
	update_shlvl(data);
	update_env_tab(data);
}

void	init_data(t_data *data, char **env)
{
	data->env = NULL;
	data->input = NULL;
	data->env_tab = NULL;
	data->token = NULL;
	data->ast = NULL;
	data->err = 0;
	data->exit_err = 0;
	data->err_msg = NULL;
	data->last_cmd_pid = 0;
	data->is_nl = false;
	data->syntax = 0;
	data->input = NULL;
	data->i = 0;
	init_env(data, env);
	if (init_sig_handler() == false)
	{
		ft_printf("minishell: Fail to init sig_handler\n");
		exit_error(data);
	}
	data->input = NULL;
}
