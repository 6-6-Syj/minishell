#include "minishell.h"
#include "libft.h"

t_type	get_operator_type(t_token *token)
{
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
	if (is_operator(token->content[0]) && (is_operator(token->content[len - 1])))
		return (get_operator_type(token));
	else if (is_quote(token->content[0]) && is_quote(token->content[len - 1]))
		return (get_quote_type(token));
	else if (is_space(token->content[0]))
		return (SPACE);
	// else if (token->content[0] == ' ')
		// return (SPACE);
	else if (is_part_of_word(token->content[0]))
		return (WORD);
	return (UNKNOWN);
}