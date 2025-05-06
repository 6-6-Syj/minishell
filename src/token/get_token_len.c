/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:20:13 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/06 05:38:07 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"


int	get_word_len(char *token)
{
	int	i;

	i = 0;
	while (token[i] && !is_a_delimiter(token[i]))
		i++;
	return (i);
}
// int	get_expand_len(char *token)

int	get_quote_len(char *token)
{
	char	quote;
	int	i;
	
	quote = token[0];
	i = 1;
	while (token[i] && token[i] != quote)
		i++;
	return (i + 1);
}

int	get_space_len(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] == C_SPACE)
		i++;
	return (i);
}

// int	get_token_len(char *token)
// {
// /* 	if (is_a_parentheses(token))
// 		return (get_parentheses_len(token));
// 	if (is_a_operator(token))
// 		return (get_operator_len(token));
// 	if (is_a_pipe(token))
// 		return (get_pipe_len(token));
// 	if (is_a_redirection(token))
// 		return(get_redirection_len); */
// 	if (token[0] == C_SIMPLE_QUOTE)
// 		return (get_simple_quote_len(token));
// 	else if (token[0] == C_DOUBLE_QUOTE)
// 		return (get_double_quote_len(token));
// 	else if (token[0] == C_SPACE)
// 		return (get_space_len(token));
// 	else
// 		return (get_word_len(token));
// 	return (0);
// }

int	get_token_len(char *token)
{
/* 	if (is_a_parentheses(token))
		return (get_parentheses_len(token));
	if (is_a_operator(token))
		return (get_operator_len(token));
	if (is_a_pipe(token))
		return (get_pipe_len(token));
	if (is_a_redirection(token))
		return(get_redirection_len); */
	if (token[0] == C_SIMPLE_QUOTE || *token == C_DOUBLE_QUOTE)
		return (get_quote_len(token));
	else if (token[0] == C_SPACE)
		return (get_space_len(token));
	else
		return (get_word_len(token));
	return (0);
}