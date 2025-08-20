/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:10:05 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/08/20 17:10:05 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_command(t_token *token_node)
{
	while (token_node)
	{
		if (token_node->type == CMD)
			return (false);
		token_node = token_node->next;
	}
	return (true);
}

int	get_args_len(t_token *token)
{
	t_token	*tmp;
	int		arg;

	tmp = token;
	arg = 0;
	while (tmp && (tmp->type == ARG || tmp->type == CMD || tmp->type == SPACE))
	{
		if (tmp->type == ARG || tmp->type == CMD)
			arg++;
		tmp = tmp->next;
	}
	return (arg);
}

t_token	*get_prev_priority_token(t_token *root_token)
{
	int		priority;
	t_token	*tmp;

	priority = root_token->priority;
	while (priority <= 2)
	{
		tmp = root_token->prev;
		while (tmp)
		{
			if (tmp->priority == priority)
				return (tmp);
			tmp = tmp->prev;
		}
		priority++;
	}
	return (NULL);
}

t_token	*get_next_priority_token(t_token *root_token)
{
	int		priority;
	t_token	*tmp;

	priority = root_token->priority + 1;
	while (priority <= 2)
	{
		tmp = root_token->next;
		while (tmp)
		{
			if (tmp->priority == priority)
				return (tmp);
			tmp = tmp->next;
		}
		priority++;
	}
	return (NULL);
}

t_token	*get_root_token(t_token **token_lst, int priority)
{
	t_token	*tmp;
	t_token	*root_token;

	root_token = NULL;
	while (priority <= 2)
	{
		tmp = *token_lst;
		while (tmp)
		{
			if (tmp->priority == priority)
				root_token = tmp;
			tmp = tmp->next;
		}
		if (root_token)
			return (root_token);
		priority++;
	}
	return (root_token);
}
