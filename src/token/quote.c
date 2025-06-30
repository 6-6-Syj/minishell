#include "minishell.h"
#include "libft.h"

bool	is_in_quote(char *token, int pos)
{
	int		i;
	bool	in_quote;

	i = 0;
	in_quote = false;
	while (token[i] && i < pos)
	{
		if (token[i] == '\"' && in_quote == false)
			in_quote = true;
		if (token[i] == '\"' && in_quote == true)
			in_quote = false;
		i++;
	}
	return (in_quote);
}

void	remove_quote(char **token_content)
{
	char	*buff;
	int		len;

	len = ft_strlen(*token_content);
	buff = ft_substr(*token_content, 1, len - 2);
	free(*token_content);
	*token_content = buff;
}

void	remove_simple_quote(t_token **token_lst, t_data *data)
{
	t_token	*current;

	current = *token_lst;
	while (current)
	{
		if (current->type == QUOTE_S)
		{
			remove_quote(&current->content);
			current->type = WORD;
		}
		if (!current->content)
			exit_error(data);
		current = current->next;
	}
}

void	remove_double_quote(t_token **token_lst, t_data *data)
{
	t_token	*current_token;

	current_token = *token_lst;
	while (current_token)
	{
		if (current_token->type == QUOTE_D)
		{
			remove_quote(&current_token->content);
			if (current_token->content[0] == '\0')
			{
				remove_node(current_token, data);
				return ;
			}
			current_token->type = WORD;
		}
		if (!current_token->content)
			exit_error(data);
		current_token = current_token->next;
	}
}