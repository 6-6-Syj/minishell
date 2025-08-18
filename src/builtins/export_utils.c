/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-18 21:22:38 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-18 21:22:38 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static bool	is_special_char(char c)
{
	if (c > '!' && c < '*')
		return (true);
	if (c >= ':' && c <= '?' && c != '=' && c != '@' && c != '#' && c != '^')
		return (true);
	if (c >= '[' && c <= ']')
		return (true);
	if (c > '{' && c < '}')
		return (true);
	if (c == '|' || c == '"' || c == '$' || c == '&' || c == ';')
		return (true);
	if (c == '<' || c == '>' || c == '~' || c == '`')
		return (true);
	return (false);
}

bool	got_special_char(char *key)
{
	int	i;

	i = 1;
	while (key && key[i])
	{
		if (is_special_char(key[i]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
			ft_putchar_fd(key[i], STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_key_valid(char *key)
{
	int	i;

	if (!key || (key[0] != '_' && !ft_isalpha(key[0])))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (false);
	}
	i = 0;
	while (key[i])
	{
		if (key[i] == '-' || key[i] == '!' || key[i] == '@' || key[i] == '#'
			|| key[i] == '*' || key[i] == '^' || key[i] == '{' || key[i] == '}'
			|| (key[i] == '+' && key[i + 1] != '=' ) || key[i] == '.')
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(key, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}
