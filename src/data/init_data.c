/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-03 21:39:20 by jmagand           #+#    #+#             */
/*   Updated: 2025-07-03 21:39:20 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "handle_signal.h"
#include "minishell.h"
#include <unistd.h>

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

static void	init_env_i(t_data *data) // TODO: CONTINUE THIS
{
	t_env	*new_env;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/");
	new_env = add_env_node(&data->env);
	if (!new_env)
		exit_error(data);
	new_env->key = ft_strdup("PWD");
	new_env->value = ft_strdup(pwd);
	new_env->print_env = true;
	new_env->print_exp = true;
	new_env = add_env_node(&data->env);
	if (!new_env)
		exit_error(data);
	new_env->key = ft_strdup("SHLVL");
	new_env->value = ft_strdup("1");
	new_env->print_env = true;
	new_env->print_exp = true;
	new_env = add_env_node(&data->env);
	if (!new_env)
		exit_error(data);
	new_env->key = ft_strdup("_");
	new_env->value = ft_strdup("minishell");
	new_env->print_env = false;
	new_env->print_exp = false;
	free(pwd);
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
				exit_error(data);
			if (!is_set_env(new_env, env[i]))
				exit_error(data);
			if (!data->env)
				data->env = new_env;
			i++;
		}
	}
	update_env_tab(data);
}

void	init_data(t_data *data, char **env)
{
	data->env = NULL;
	data->env_tab = NULL;
	data->token = NULL;
	data->ast = NULL;
	data->err = 0;
	data->exit_err = 0;
	data->err_msg = NULL;
	data->pid_list = NULL;
	init_env(data, env);
	if (init_sig_handler() == false)
	{
		ft_printf("(init_data) FAIL to init sig handler\n");
		exit_error(data);
	}
	data->input = NULL;
}
