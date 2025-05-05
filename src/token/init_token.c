/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:21:31 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 22:18:31 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	set_token_value(t_token *token)
{
	if (token->content[0] == '(')
		token->value = TYPE_PARENTHESE;
	if (token->content[0] == '&' && token->content[1] == '&')
		token->value = TYPE_REDIRECTION;
/* 	if (is_a_pipe(token))
		set_pipe;
	if (is_a_redirection(token))
		set_redirection;
	if (is_a_command(token))
		set command;
	if (is_a_expand(token))
		set expand;
	if (is_a_quote(token))
		set quote;
	if (is_a_space)
		set_space; */
}

void	set_token_content(t_token *token, char *content)
{
	int		len;

	len = get_token_len(content);
	token->content = ft_strndup(content, len);
}

t_token	*add_token_node(t_token *token_lst)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL); // NEED PROTEC
	if (!token_lst)
	{
		token_lst = new_node;
		new_node->prev = NULL; // NEEDED ?
	}
	else
	{
		last_node = get_last_token(token_lst);
		last_node->next = new_node;
		new_node->prev = last_node; // NEEDED ? 
	}
	new_node->next = NULL;
	return (new_node);
}

void	init_token(t_token *token_lst, char *input)
{
	t_token	*new_token;
	int		i;

	token_lst = NULL;
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		new_token = add_token_node(token_lst);
		set_token_content(new_token, &input[i]);
		// set_token_value(new_token);
		i += get_token_len(&input[i]);
	}
}
