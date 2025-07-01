#include "minishell.h"
#include "libft.h"

#

void	free_expand_buffer(char *first, char *last)
{
	if (first)
		free(first);
	if (last)
		free(last);
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
			free_expand_buffer(first, last);
		}
		i++;
	}
	return (token);
}

void	expand_var(t_token **token_lst, t_data *data)
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

// void	remove_wrong_expand(t_token **token_lst, t_data *data)
// {
// 	t_token	*current;
// 	t_token	*tmp;

// 	(void)data;
// 	current = *token_lst;
// 	while (current)
// 	{
// 		tmp = current->next;
// 		if (ft_strcmp(current->content, "$") == 0)
// 			remove_node(current, data);
// 		current = tmp;
// 	}
// }