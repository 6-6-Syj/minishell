/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/05 17:40:07 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 17:40:07 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdio.h>
#include <unistd.h>


bool	is_metachar(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (true);
	if (ft_strcmp(token, ">") == 0)
		return (true);
	if (ft_strcmp(token, "<<") == 0)
		return (true);
	if (ft_strcmp(token, ">>") == 0)
		return (true);
	if (ft_strcmp(token, "|") == 0)
		return (true);
	if (ft_strcmp(token, "||") == 0)
		return (true);
	if (ft_strcmp(token, "&&") == 0)
		return (true);
	if (ft_strcmp(token, "(") == 0)
		return (true);
	if (ft_strcmp(token, ")") == 0)
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	// if (c == '$')
	// 	return (true);
	if (c == '|')
		return (true);
	if (c == '&')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\"')
		return (true);
	if (c == '\'')
		return (true);
	return (false);
}

bool	is_parenthesis(char c)
{
	if (c == '(' || c == ')')
		return (true);
	return (false);
}

bool	is_part_of_word(char c)
{
	if (c == '(' || c == ')')
		return (false);
	if (c == '&' || c == '|')
		return (false);
	// else if (c == '$')
	// 	return (false);
	else if (c == '\"')
		return (false);
	else if (c == '\'')
		return (false);
	else if (c == '<')
		return (false);
	else if (c == '>')
		return (false);
	else if (c == ' ')
		return (false);
	return (true);
}

t_type	get_token_word_type(t_token *current)
{
	// TODO: handle here_doc delimiter
	// TODO: handle expand + pipe
	// TODO: secure if current is NULL ?
	t_token *prev_token;

	// if (ft_strlen(current->content) > 1 && )
	prev_token = current->prev;
	while (prev_token && (prev_token->type == TYPE_SPACE))
		prev_token = prev_token->prev;
	// if (ft_strlen(current->content) > 1 && current->content[0] == '$')
	// return (TYPE_EXPAND);
	// if (current->prev->type == TYPE_EXPAND)
	// 	return (TYPE_VAR);
	if (!prev_token)
		return (TYPE_CMD);
	if (prev_token->type == TYPE_CMD)
		return (TYPE_ARG);
	if (prev_token->type == TYPE_REDIR_APPEND)
		return (TYPE_FILE);
	if (prev_token->type == TYPE_REDIR_IN)
		return (TYPE_FILE);
	if (prev_token->type == TYPE_HERE_DOC)
		return (TYPE_FILE);
	if (prev_token->type == TYPE_REDIR_OUT)
		return (TYPE_FILE);
	if (prev_token->type == TYPE_FILE)
		return (TYPE_ARG);
	if (prev_token->type == TYPE_ARG)
		return (TYPE_ARG);
	return (TYPE_CMD);
}

t_type	get_operator_type(t_token *token)
{
	// if (ft_strcmp(token->content, "$") == 0)
	// 	return (TYPE_EXPAND);
	if (ft_strcmp(token->content, "<") == 0)
		return (TYPE_REDIR_IN);
	else if (ft_strcmp(token->content, "<<") == 0)
		return (TYPE_HERE_DOC);
	else if (ft_strcmp(token->content, ">") == 0)
		return (TYPE_REDIR_OUT);
	else if (ft_strcmp(token->content, ">>") == 0)
		return (TYPE_REDIR_APPEND);
	else if (ft_strcmp(token->content, "|") == 0)
		return (TYPE_PIPE);
	else if (ft_strcmp(token->content, "||") == 0)
		return (TYPE_OR);
	else if (ft_strcmp(token->content, "&&") == 0)
		return (TYPE_AND);
	return (TYPE_UNKNOWN);
}

t_type	get_quote_type(t_token *token)
{
	if (token->content[0] == '\"' && ft_strchr(token->content + 1, '"'))
		return (TYPE_QUOTE_D);
	else if (token->content[0] == '\'' && ft_strchr(token->content + 1, '\''))
		return (TYPE_QUOTE_S);
	return (TYPE_UNKNOWN);
}

t_type	get_token_type(t_token *token)
{
	int len;

	len = ft_strlen(token->content);
	if (token->content[0] == '(')
		return (TYPE_PAREN_L);
	else if (token->content[0] == ')')
		return (TYPE_PAREN_R);
	else if (is_operator(token->content[0]) && (is_operator(token->content[len - 1])))
		return (get_operator_type(token));
	else if (is_quote(token->content[0]) && is_quote(token->content[len - 1]))
		return (get_quote_type(token));
	else if (token->content[0] == ' ')
		return (TYPE_SPACE);
	else if (is_part_of_word(token->content[0]))
		return (TYPE_WORD);
	return (TYPE_UNKNOWN);
}

int	get_token_priority(t_token *token)
{
	if (token->type == TYPE_PAREN_L || token->type == TYPE_PAREN_R)
		return (0);
	else if (token->type == TYPE_PIPE)
		return (1);
	else if (token->type == TYPE_HERE_DOC)
		return (2);
	else if (token->type == TYPE_REDIR_IN || token->type == TYPE_REDIR_OUT
		|| token->type == TYPE_REDIR_APPEND)
		return (3);
	else if (token->type == TYPE_OR || token->type == TYPE_AND)
		return (4);
	else if (token->type == TYPE_CMD)
		return (5);
	return (-1);
}
