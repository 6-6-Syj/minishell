/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:21:31 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/07 06:14:18 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "unistd.h"
#include "libft.h"

t_type	get_token_type(char *token)
{
	if (token[0] == '(')
		return (TYPE_PAREN_L);
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
	return (TYPE_UNKNOW);
}

void	set_token(t_token **token, char *content)
{
	int		len;

	len = get_token_len(content);
	(*token)->content = ft_strndup(content, len);
	(*token)->type = get_token_type((*token)->content);
}

t_token	*add_token_node(t_token **token_lst)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL); // NEED PROTEC
	if (!*token_lst)
	{
		*token_lst = new_node;
		new_node->prev = NULL; // NEEDED ?
	}
	else
	{
		last_node = get_last_token(*token_lst);
		last_node->next = new_node;
		new_node->prev = last_node; // NEEDED ? 
	}
	new_node->next = NULL;
	return (new_node);
}

void	init_token(t_token **token_lst, char *input)
{
	t_token	*new_token;
	int		i;

	*token_lst = NULL;
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		new_token = add_token_node(token_lst);
		set_token(&new_token, &input[i]);
		i += get_token_len(&input[i]);
	}
}
