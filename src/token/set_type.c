/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:27:26 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/20 16:46:38 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	set_command_type(t_token **token_lst)
{
	t_token	*token_node;
	t_token	*tmp;

	token_node = *token_lst;
	while (token_node)
	{
		tmp = token_node->next;
		if (token_node->type == WORD)
		{
			token_node->type = CMD;
			while (tmp && tmp->type != PIPE)
			{
				if (tmp->type == WORD)
					tmp->type = ARG;
				tmp = tmp->next;
			}
		}
		token_node = token_node->next;
	}
}

void	set_token_type(t_token **token_lst, t_data *data)
{
	t_token	*token_node;

	(void)data;
	token_node = *token_lst;
	while (token_node)
	{
		token_node->type = get_token_type(token_node);
		// if (token_node->type == UNKNOWN)
		// 	syntax_error(data);
		token_node = token_node->next;
	}
}

void	set_file_type(t_token **token_lst)
{
	t_token	*token_node;

	token_node = *token_lst;
	while (token_node)
	{
		if (token_node->type & REDIR && token_node->next)
		{
			if (token_node->next->type == SPACE)
				token_node = token_node->next;
			if (token_node->next->type == WORD)
				token_node->next->type = REDIR_TARGET;
		}
		token_node = token_node->next;
	}
}
