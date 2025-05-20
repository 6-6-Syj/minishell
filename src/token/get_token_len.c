/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:20:13 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/20 17:20:18 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	get_token_len(char *token)
{
	int	i;

	i = 1;
	if (token[0] == '(' || token[0] == ')')
		return (1);
	while  (token[i])
	{
		if (token[0] == '<' && token[i] != '<')
			return (i);
		else if (token[0] == '>' && token[i] != '>')
			return (i);
		else if (token[0] == '|' && token[i] != '|')
			return (i);
		else if (token[0] == '&' && token[i] != '&')
			return (i);
		else if (token[0] == '\"' && token[i] == '\"')
			return (i + 1);
		else if (token[0] == '\'' && token[i] == '\'')
			return (i + 1);
		else if (token[0] == ' ' && token[i] != ' ')
			return (i);
		else if (!is_delimiter(token[0]) && is_delimiter(token[i]))
			return (i);
		i++;
	}
	return (i);
}
