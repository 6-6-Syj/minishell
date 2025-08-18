/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-04 18:58:47 by jmagand           #+#    #+#             */
/*   Updated: 2025-07-04 18:58:47 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static char	*get_pwd_i(t_data *data)
{
	char	*pwd;
	char	path[PATH_MAX];

	pwd = getcwd(path, PATH_MAX);
	if (!pwd)
	{
		pwd = ft_strdup("/");
		if (!pwd)
			malloc_failed(data, NULL);
	}
	else
	{
		pwd = ft_strdup(path);
		if (!pwd)
			malloc_failed(data, NULL);
	}
	return (pwd);
}

static void	init_pwd_i(t_data *data)
{
	t_env	*new_env;
	char	*pwd;

	pwd = get_pwd_i(data);
	new_env = add_env_node(&data->env);
	if (!new_env)
		malloc_failed(data, pwd);
	new_env->key = ft_strdup("PWD");
	if (!new_env->key)
		malloc_failed(data, pwd);
	new_env->value = ft_strdup(pwd);
	if (!new_env->value)
	{
		free(new_env->key);
		malloc_failed(data, pwd);
	}
	new_env->print_env = true;
	new_env->print_exp = true;
	free(pwd);
}

static void	init_shlvl_i(t_data *data)
{
	t_env	*new_env;

	new_env = add_env_node(&data->env);
	if (!new_env)
		malloc_failed(data, NULL);
	new_env->key = ft_strdup("SHLVL");
	if (!new_env->key)
		malloc_failed(data, NULL);
	new_env->value = ft_strdup("1");
	if (!new_env->value)
	{
		free(new_env->key);
		malloc_failed(data, NULL);
	}
	new_env->print_env = true;
	new_env->print_exp = true;
}

static void	init_oldpwd_i(t_data *data)
{
	t_env	*new_env;

	new_env = add_env_node(&data->env);
	if (!new_env)
		malloc_failed(data, NULL);
	new_env->key = ft_strdup("_");
	if (!new_env->key)
		malloc_failed(data, NULL);
	new_env->print_env = false;
	new_env->print_exp = true;
}

void	init_env_i(t_data *data)
{
	init_oldpwd_i(data);
	init_pwd_i(data);
	init_shlvl_i(data);
	init_underscore_i(data);
}
