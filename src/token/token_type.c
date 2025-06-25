#include "token.h"

t_type	get_token_word_type(t_token *current)
{
	// TODO: handle expand + pipe
	// TODO: secure if current is NULL ?
	t_token *prev_token;

	// if (ft_strlen(current->content) > 1 && )
	prev_token = current->prev;
	while (prev_token && prev_token->type == SPACE)
		prev_token = prev_token->prev;
	// if (ft_strlen(current->content) > 1 && current->content[0] == '$')
		// return (EXPAND);
	if (!prev_token)
		return (CMD);
	// if (current->prev->type == EXPAND)
	// 	return (VAR);
	if (prev_token->type == CMD)
		return (ARG);
	if (prev_token->type == REDIR_APPEND)
		return (ARG);
	if (prev_token->type == REDIR_IN)
		return (ARG);
	if (prev_token->type == HERE_DOC)
		return (ARG);
	if (prev_token->type == REDIR_OUT)
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
	int	len;

	len = ft_strlen(token->content);
	// if (token->content[0] == '(')
	// 	return (PAREN_L);
	// else if (token->content[0] == ')')
	// 	return (PAREN_R);
	if (is_operator(token->content[0]) && (is_operator(token->content[len - 1])))
		return (get_operator_type(token));
	else if (is_quote(token->content[0]) && is_quote(token->content[len - 1]))
		return (get_quote_type(token));
	else if (token->content[0] == ' ')
		return (SPACE);
	else if (is_part_of_word(token->content[0]))
		return (WORD);
	return (UNKNOWN);
}