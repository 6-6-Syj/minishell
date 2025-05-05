/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:20:13 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 22:19:59 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	get_space_len(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] == C_SPACE)
		i++;
	return (i);
}

int	get_simple_quote_len(char *token)
{
	int	i;

	i = 1;
	while (token[i] && token[i] != C_SIMPLE_QUOTE)
		i++;
	return (i + 1);
}

int	get_double_quote_len(char *token)
{
	int	i;

	i = 1;
	while (token[i] && token[i] != C_DOUBLE_QUOTE)
		i++;
	return (i + 1);
}

int	get_word_len(char *token)
{
	int	i;

	i = 0;
	while (token[i] && !is_a_delimiter(token[i]))
		i++;
	return (i);
}

int	get_token_len(char *token)
{
/* 	if (is_a_parentheses(token))
		return (get_parentheses_len(token));
	if (is_a_operator(token))
		return (get_simple_quote_len(token));
	if (is_a_pipe(token))
		return(get_simple_quote_len); */
	if (token[0] == C_SIMPLE_QUOTE)
		return (get_simple_quote_len(token));
	else if (token[0] == C_DOUBLE_QUOTE)
		return (get_double_quote_len(token));
	else if (token[0] == C_SPACE)
		return (get_space_len(token));
	else
		return (get_word_len(token));
	return (0);
}
