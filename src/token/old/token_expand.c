#include "minishell.h"

void	remove_wrong_expand(t_token **token_lst, t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	(void)data;
	current = *token_lst;
	while (current)
	{
		tmp = current->next;
		if (ft_strcmp(current->content, "$") == 0)
			remove_node(current, data);
		current = tmp;
	}
}

void	parse_expand(t_token **token_lst, t_data *data)
{
	t_token	*current_token;

	current_token = *token_lst;
	while (current_token)
	{
		if (current_token->type != QUOTE_S)
			current_token->content = handle_expand(current_token->content,
					data);
		current_token = current_token->next;
	}
}
char	*concatenate_expand(char *first, char *inter, char *last, t_data *data)
{
	char	*buff;
	char	*dst;

	buff = ft_strjoin(first, inter);
	dst = ft_strjoin(buff, last);
	free(buff);
	if (!dst)
		exit_error(data);
	return (dst);
}

bool	is_expand(char *token_content)
{
	int	i;

	i = 0;
	if (!token_content[i] || !token_content[i + 1])
		return (false);
	if (token_content[i] == '$')
		return (true);
	return (false);
}

int	get_expand_len(char *token_content)
{
	int	i;

	i = 1;
	if (!token_content)
		return (0);
	while (token_content[i] && is_part_of_word(token_content[i]))
		i++;
	return (i);
}

char	*get_expand(char *token, t_data *data)
{
	char	*expand_key;
	char	*expand_value;
	int		len;

	len = get_expand_len(token);
	expand_key = ft_substr(token, 1, len - 1);
	// if (!expand_key)
	// 	exit_error(data);
	expand_value = get_env_var(data, expand_key);
	return (expand_value);
}

char	*handle_expand(char *token, t_data *data)
{
	char	*first;
	char	*expand;
	char	*last;
	int		len;
	int		i;

	i = 0;
	while (token && token[i])
	{
		if (is_expand(&token[i]))
		{
			expand = get_expand(&token[i], data);
			len = get_expand_len(&token[i]);
			first = ft_substr(token, 0, i); // secu
			i += len;
			last = ft_strdup(&token[i]); // secu
			free(token);
			token = concatenate_expand(first, expand, last, data);
			// free_expand_buffer(first, expand, last);
		}
		i++;
	}
	return (token);
}