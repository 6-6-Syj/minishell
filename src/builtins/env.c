/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:54:26 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:13:10 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// static bool	check_equal(char *str)
// {
// 	char *equal_pos;

// 	if (!str || !*str)
// 		return (false);
// 	equal_pos = ft_strchr(str, '=');
// 	if (!equal_pos || equal_pos == str)
// 		return (false);
// 	return (true);
// }

int	ft_env(t_env *env_lst)
{
	t_env	*current;

	current = env_lst;
	while (current)
	{
		if (current->key && current->value)
		{
			ft_putstr_fd(current->key, 1);
			write(1, "=", 1);
			ft_putstr_fd(current->value, 1);
			write(1, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}

// NO ERROR CODE
	// If no env, no path, so command cant be executed
	// else env -> PATH= -> no error.
