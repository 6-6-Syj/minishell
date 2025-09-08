/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:47:08 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/08 19:08:46 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"
#include "redir.h"
#include "token.h"

bool	is_ambiguous_redir(t_token *token)
{
	while (token && token->type != PIPE && token->type != REDIR_AMBIGUOUS
		&& token->type != REDIR_TARGET)
	{
		if (token->type == REDIR_AMBIGUOUS)
			return (true);
		token = token->next;
	}
	return (false);
}

static int	set_redir_node(t_redir *redir_node, t_token *token_node,
		t_data *data)
{
	if (!token_node || !token_node->next)
		return (-1);
	redir_node->type = token_node->type;
	redir_node->is_ambiguous = false;
	if (token_node->type == HERE_DOC)
	{
		redir_node->delimiter = get_redir_delimiter(token_node, data);
		if (!redir_node->delimiter)
		{
			data->err = 2;
			exit_error(data);
		}
		if (redir_node->delimiter[0])
			set_here_doc(&redir_node, data);
	}
	else if (token_node->type & REDIR)
	{
		redir_node->filename = get_redir_target(&token_node);
		if (!redir_node->filename)
			return (-1);
	}
	if (is_ambiguous_redir(token_node))
		redir_node->is_ambiguous = true;
	return (0);
}

static t_redir	*add_redir_node(t_redir **redir_lst)
{
	t_redir	*new_node;
	t_redir	*last_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
		return (NULL);
	if (!*redir_lst)
	{
		*redir_lst = new_node;
		new_node->next = NULL;
	}
	else
	{
		last_node = get_last_redir_node(*redir_lst);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
	return (new_node);
}

void	init_redir(t_token *token_node, t_redir **redir_lst, t_data *data)
{
	t_redir	*new_redir;

	new_redir = *redir_lst;
	token_node = get_first_redir(&token_node);
	while (token_node)
	{
		if (token_node->type & REDIR)
		{
			new_redir = add_redir_node(redir_lst);
			if (!new_redir)
				malloc_fail(data);
			if (set_redir_node(new_redir, token_node, data) == -1)
				return ;
			token_node = get_next_redir(&token_node);
		}
	}
}
