/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:42:06 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 16:08:46 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static bool	redir_is_valid(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		if (token->type & REDIR)
		{
			tmp = token->next;
			while (tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (!tmp || tmp->type != REDIR_TARGET)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

static bool	pipe_is_valid(t_token *token)
{
	t_token	*tmp;
	int		cmd_count;
	int		redir_count;

	while (token)
	{
		if (token->type == PIPE)
		{
			tmp = token->next;
			cmd_count = 0;
			redir_count = 0;
			while (tmp && tmp->type != PIPE)
			{
				if (tmp->type == CMD)
					cmd_count++;
				else if (tmp->type & REDIR)
					redir_count++;
				tmp = tmp->next;
			}
			if (cmd_count != 1 && redir_count < 1)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

static bool	type_is_unknow(t_token *token)
{
	while (token)
	{
		if (token && token->type == UNKNOWN)
			return (true);
		token = token->next;
	}
	return (false);
}

bool	syntax_is_valid(t_token *token)
{
	if (type_is_unknow(token))
		return (false);
	if (!pipe_is_valid(token))
		return (false);
	if (!redir_is_valid(token))
		return (false);
	if (token->type == PIPE)
		return (false);
	return (true);
}
