/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:00:43 by jmagand           #+#    #+#             */
/*   Updated: 2025/09/08 21:17:41 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "data.h"
#include "libft.h"
#include "redir.h"

t_token	*get_first_redir(t_token **root_token)
{
	t_token	*token_node;
	t_token	*tmp;

	if (!*root_token)
		return (NULL);
	token_node = *root_token;
	while (token_node->prev && token_node->prev->type != PIPE)
		token_node = token_node->prev;
	while (token_node && token_node->type != PIPE)
	{
		tmp = token_node->next;
		if (token_node->type & REDIR)
		{
			while (tmp && tmp->type != REDIR_TARGET
				&& tmp->type != REDIR_AMBIGUOUS)
				tmp = tmp->next;
			if (tmp)
				return (token_node);
		}
		token_node = token_node->next;
	}
	return (NULL);
}

t_token	*get_next_redir(t_token **root_token)
{
	t_token	*token_node;
	t_token	*tmp;

	if (!*root_token || !(*root_token)->next)
		return (NULL);
	token_node = (*root_token)->next;
	while (token_node && token_node->type != PIPE)
	{
		
		tmp = token_node;
		if (token_node->type & REDIR)
		{
			while (tmp && tmp->type != REDIR_TARGET
				&& tmp->type == REDIR_AMBIGUOUS)
				tmp = tmp->next;
			if (tmp)
				return (token_node);
		}
		token_node = token_node->next;
	}
	return (NULL);
}

t_redir	*get_last_redir_node(t_redir *current)
{
	if (!current)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

char	*get_redir_delimiter(t_token *token, t_data *data)
{
	char	*delimiter;

	while (token && token->type != PIPE)
	{
		if (token->type == REDIR_TARGET || token->type == REDIR_AMBIGUOUS)
		{
			delimiter = ft_strdup(token->content);
			if (!delimiter)
				malloc_fail(data);
			return (delimiter);
		}
		token = token->next;
	}
	return (NULL);
}

char	*get_redir_target(t_token **root_token)
{
	t_token	*token;
	char	*redir_target;

	if (!*root_token || !(*root_token)->next)
		return (NULL);
	token = (*root_token)->next;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR_TARGET || token->type == REDIR_AMBIGUOUS)
		{
			redir_target = ft_strdup(token->content);
			return (redir_target);
		}
		token = token->next;
	}
	return (NULL);
}
