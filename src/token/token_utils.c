/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:40:07 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 17:40:07 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "token.h"

// bool	is_a_delimiter(char c)
// {
// 	if (c == '(' || c == ')')
// 		return (true);
// 	if (c == C_SIMPLE_QUOTE || c == C_DOUBLE_QUOTE)
// 		return (true);
// 	if (c == C_SPACE)
// 		return (true);
// 	return (false);
// }

t_token	*get_last_token(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}
bool	is_delimiter(char c)
{
	if (c == '(' || c == ')')
		return (true);
	if (c == '&' || c == '|')
		return (true);
	else if (c == '\"')
		return (true);
	else if (c == '\'')
		return (true);
	else if (c == '<')
		return (true);
	else if (c == '>')
		return (true);
	else if (c == ' ')
		return (true);
	return (false);
}