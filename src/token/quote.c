#include "libft.h"
#include "minishell.h"

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
	if (len == 2) /////////////////////////////
		buff = ft_calloc(1, 1);
	// else if (len == 3)
	// 	buff = ft_substr(*token_content, 1, 2);
	else
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
			if (current->content[0] == '\0')
				remove_node(current, data);
			current->type = WORD;
		}
		if (!current->content)
			remove_node(current, data);
		current = current->next;
	}
}

void	remove_double_quote(t_token **token_lst, t_data *data)
{
	t_token *current;
	t_token	*tmp;

	current = *token_lst;
	while (current)
	{
		tmp = current->next;
		if (current->type == QUOTE_D)
		{
			remove_quote(&current->content);
			current->type = WORD;
			if (current->content[0] == '\0')
				remove_node(current, data);
		}
		if (!current->content)
			remove_node(current, data);
		current = tmp;
	}
}
