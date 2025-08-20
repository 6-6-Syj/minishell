/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:46:49 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/08/20 16:46:58 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == '|')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\"')
		return (true);
	if (c == '\'')
		return (true);
	return (false);
}

bool	is_part_of_word(char c)
{
	if (c == '|')
		return (false);
	else if (c == '\"')
		return (false);
	else if (c == '\'')
		return (false);
	else if (c == '<')
		return (false);
	else if (c == '>')
		return (false);
	else if (c == ' ' || (c >= 9 && c <= 13))
		return (false);
	return (true);
}
