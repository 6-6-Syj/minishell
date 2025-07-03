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

/*
	NO ERROR CODE
		If no env, no path, so command cant be executed
			else env got PATH="smtg/ok/", so NO error.
*/

int	ft_env(t_env *env_lst)
{
	t_env	*current;

	current = env_lst;
	while (current && current->prev)
		current = current->prev;
	while (current)
	{
		if (current->key && current->value && current->print_env)
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		current = current->next;
	}
	return (NO_ERROR);
}
