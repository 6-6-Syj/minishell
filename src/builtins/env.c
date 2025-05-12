/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:54:26 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:25:16 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// (POSIX) Undeterminated order to show variables

int	ft_env(t_env *env_lst)
{
	t_env	*current;

	current = env_lst;
	while (current)
	{
		if (current->print_env)
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
	}
	return (NO_ERROR);
}

// NO ERROR CODE
	// If no env, no path, so command cant be executed
	// else env got PATH="smtg/ok/", so NO error.
