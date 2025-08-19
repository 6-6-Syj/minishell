#include "libft.h"
#include "minishell.h"

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

	buff = ft_strjoin(first, inter);
	if (ft_strlen(buff) != (ft_strlen(first) + ft_strlen(inter)))
	{
		free_expand_buffer(first, inter, last);
		malloc_fail(data);
	}
	dst = ft_strjoin(buff, last);
	if (ft_strlen(dst) != (ft_strlen(buff) + ft_strlen(last)))
	{
		free_expand_buffer(first, inter, last);
		malloc_fail(data);
	}
	if (buff)
		free(buff);
	free_expand_buffer(first, inter, last);
	return (dst);
}

char	*handle_expand(char *token, int i, t_data *data)
{
	char	*first;
	char	*expand;
	char	*last;

	while (token && token[i])
	{
		if (is_expand(&token[i]))
		{
			first = ft_substr(token, 0, i);
			if (ft_strlen(first) != ((size_t)i))
				malloc_fail(data);
			expand = get_expand(&token[i], data);
			i += (get_expand_key_len(&token[i]) + 1);
			last = ft_strdup(&token[i]);
			if (!last)
			{
				free_expand_buffer(first, expand, last);
				malloc_fail(data);
			}
			free(token);
			token = concatenate_expand(first, expand, last, data);
			i = 0;
		}
		i++;
	}
	return (token);
}

void	expand_var(t_token **token_lst, t_data *data)
{
	t_token	*current;

	current = *token_lst;
	while (current)
	{
		if (current->content && current->type != QUOTE_S)
		{
			current->content = handle_expand(current->content, 0, data);
		}
		current = current->next;
	}
}
