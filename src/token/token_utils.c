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
	while (prev_token && (prev_token->type == SPACE))
		prev_token = prev_token->prev;
	// if (ft_strlen(current->content) > 1 && current->content[0] == '$')
	// return (EXPAND);
	// if (current->prev->type == EXPAND)
	// 	return (VAR);
	if (!prev_token)
		return (CMD);
	if (prev_token->type == CMD)
		return (ARG);
	if (prev_token->type == REDIR_APPEND)
		return (REDIR_TARGET);
	if (prev_token->type == REDIR_IN)
		return (REDIR_TARGET);
	if (prev_token->type == HERE_DOC)
		return (REDIR_TARGET);
	if (prev_token->type == REDIR_OUT)
		return (REDIR_TARGET);
	if (prev_token->type == REDIR_TARGET)
		return (ARG);
	if (prev_token->type == ARG)
		return (ARG);
	return (CMD);
}

t_type	get_operator_type(t_token *token)
{
	// if (ft_strcmp(token->content, "$") == 0)
	// 	return (EXPAND);
	if (ft_strcmp(token->content, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token->content, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(token->content, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(token->content, ">>") == 0)
		return (REDIR_APPEND);
	else if (ft_strcmp(token->content, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token->content, "||") == 0)
		return (OR);
	else if (ft_strcmp(token->content, "&&") == 0)
		return (AND);
	return (UNKNOWN);
}

t_type	get_quote_type(t_token *token)
{
	if (token->content[0] == '\"' && ft_strchr(token->content + 1, '"'))
		return (QUOTE_D);
	else if (token->content[0] == '\'' && ft_strchr(token->content + 1, '\''))
		return (QUOTE_S);
	return (UNKNOWN);
}

t_type	get_token_type(t_token *token)
{
	int len;

	len = ft_strlen(token->content);
	if (token->content[0] == '(')
		return (PAREN_L);
	else if (token->content[0] == ')')
		return (PAREN_R);
	else if (is_operator(token->content[0]) && (is_operator(token->content[len - 1])))
		return (get_operator_type(token));
	else if (is_quote(token->content[0]) && is_quote(token->content[len - 1]))
		return (get_quote_type(token));
	else if (token->content[0] == ' ')
		return (SPACE);
	else if (is_part_of_word(token->content[0]))
		return (WORD);
	return (UNKNOWN);
}

int	get_token_priority(t_token *token)
{
	if (token->type == PAREN_L || token->type == PAREN_R)
		return (0);
	else if (token->type == PIPE)
		return (1);
	else if (token->type == HERE_DOC)
		return (2);
	else if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == REDIR_APPEND)
		return (3);
	else if (token->type == OR || token->type == AND)
		return (4);
	else if (token->type == CMD)
		return (5);
	return (-1);
}
