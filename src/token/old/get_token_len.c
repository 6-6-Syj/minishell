/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:20:13 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/06/23 23:42:28 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	get_token_len(char *token)
{
	int	i;

	i = 1;
	// if (is_parenthesis(token[0]))
	// 	return (1);
	while (token[i])
	{
		if (is_operator(token[0]) && !is_operator(token[i]))
			return (i);
		else if (token[0] == '\'' && token[i] == '\'')
			return (i + 1);
		else if (token[0] == '\"' && token[i] == '\"')
			return (i + 1);
		else if (token[0] == ' ' && token[i] != ' ')
			return (i);
		else if (is_part_of_word(token[0]) && !is_part_of_word(token[i]))
			return (i);
		i++;
	}
	return (i);
}
