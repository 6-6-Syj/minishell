/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:21:31 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/06/20 23:09:42 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "unistd.h"
#include "libft.h"

// TODO: remove space at the begining and the end of list;
// TODO: remove \n ?
// TODO: check if token are valid
//			-quote are corectly close
//			-parenthesis are corectly close

// TODO: check for '\' char
// TODO: check for illegal char
// TODO: error
// TODO: handle space when subshell or quote
// TODO: handle expand
// TODO: 
static int		set_token_type(t_token *token_node)
{
	token_node->type = get_token_type(token_node);
	if (token_node->type == UNKNOWN)
		return (-1);
	// if (token_node->type == WORD)
	// 	token_node->type = get_token_word_type(token_node);
	return (0);
}

static int		set_token_content(t_token *token_node, char *new_content)
{
	int	len;

	len = get_token_len(new_content);
	token_node->content = ft_strndup(new_content, len);
	if (!token_node->content)
		return (-1);
	return (0);
}

static int	set_token_priority(t_token *token_node)
{
	token_node->priority = get_token_priority(token_node);
	return (0);
}

static int	set_token_node(t_token *token_node, char *content)
{
	if (set_token_content(token_node, content))
		return (-1);
	if (set_token_type(token_node))
		return (-1);
	if (set_token_priority(token_node) == -1)
		return (-1);
	return (0);
}

int	init_token(t_token **token_lst, char *input)
{
	t_token	*new_token;
	int		i;

	// *token_lst = NULL;
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		new_token = add_token_node(token_lst);
		if (!new_token)
			return (-1);
		if (set_token_node(new_token, &input[i]) == -1)
			return(-1);
		i += get_token_len(&input[i]);
	}
	return (0);
}
