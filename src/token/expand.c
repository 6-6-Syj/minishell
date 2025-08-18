#include "minishell.h"
#include "libft.h"

void	free_expand_buffer(char *first, char *inter, char *last)
{
	if (first)
	{
		free(first);
		first = NULL;
	}
	if (inter)
	{
		free(inter);
		inter = NULL;
	}
	if (last)
	{
		free(last);
		last = NULL;
	}
}

char	*concatenate_expand(char *first, char *inter, char *last, t_data *data)
{
	char	*buff;
	char	*dst;

	// secure with len
	buff = ft_strjoin(first, inter);

	dst = ft_strjoin(buff, last);
	if (buff)
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
	int		i;

	i = 0;
	if (!token)
		return (NULL);
	while (token[i])
	{
		if (is_expand(&token[i])) //TODO: handle special char
		{
			first = ft_substr(token, 0, i); // secu
			expand = get_expand(&token[i], data);
			i += (get_expand_key_len(&token[i]) + 1);
			last = ft_strdup(&token[i]); // secu
			// i += (len + 1);
			// ft_printf("first = %s\n", first);
			// ft_printf("expand = %s\n", expand);
			// ft_printf("last = %s\n", last);
			free(token);
			token = concatenate_expand(first, expand, last, data);
			free_expand_buffer(first, expand, last);
			i = 0;
		}
		i++;
	}
	// print_all(data);
	return (token);
}

void	expand_var(t_token **token_lst, t_data *data)
{
	t_token	*current;

	current = *token_lst;
	while (current)
	{
		// if (current->content && current->type != QUOTE_S && ft_strcmp(current->content, "$?") == 0)
		// {
		// 	free(current->content);
		// 	current->content = ft_itoa(data->err);
		// }
		if (current->content && current->type != QUOTE_S)
		{
			current->content = handle_expand(current->content,
				data);
		}
		current = current->next;
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
