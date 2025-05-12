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
#include "libft.h"

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

t_type	get_token_type(char *token)
{
	if (token[0] == '(')
		return (TYPE_PAREN_L);
	if (token[0] == ')')
		return (TYPE_PAREN_R);
	else if (ft_strcmp(token, "<") == 0)
		return (TYPE_REDIR_IN);
	else if (ft_strcmp(token, "<<") == 0)
		return (TYPE_HERE_DOC);
	else if (ft_strcmp(token, ">") == 0)
		return (TYPE_REDIR_OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (TYPE_REDIR_APPEND);
	else if (ft_strcmp(token, "|") == 0)
		return (TYPE_PIPE);
	else if (ft_strcmp(token, "||") == 0)
		return (TYPE_OR);
	else if (ft_strcmp(token, "&&") == 0)
		return (TYPE_AND);
	else if (token[0] == '\"')
		return (TYPE_QUOTE_D);
	else if (token[0] == '\'')
		return (TYPE_QUOTE_S);
	else if (token[0] == ' ')
		return (TYPE_SPACE);
	else if (!is_delimiter(token[0]))
		return (TYPE_WORD);
	return (TYPE_UNKNOWN);
}
