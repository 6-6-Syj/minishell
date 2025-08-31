/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_i_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-18 21:48:17 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-18 21:48:17 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "data.h"

void	malloc_failed(t_data *data, char *pwd)
{
	if (pwd)
		free(pwd);
	data->err_msg = "Malloc failed";
	data->err = 1;
	exit_error(data);
}

void	init_underscore_i(t_data *data)
{
	t_env	*new_env;

	new_env = add_env_node(&data->env);
	if (!new_env)
		malloc_failed(data, NULL);
	new_env->key = ft_strdup("_");
	if (!new_env->key)
		malloc_failed(data, NULL);
	new_env->value = ft_strdup("minishell");
	if (!new_env->value)
	{
		free(new_env->key);
		malloc_failed(data, NULL);
	}
	new_env->print_env = false;
	new_env->print_exp = false;
}
