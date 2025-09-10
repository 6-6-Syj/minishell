/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:49:11 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/10 16:01:39 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"
#include "token.h"
#include <stdlib.h>

static void	free_expand_buffer(char *first, char *inter, char *last)
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

static char	*concatenate_expand(char *first, char *inter, char *last,
		t_data *data)
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

char	*handle_expand(char *token, int i, t_type type, t_data *data)
{
	char	*first;
	char	*expand;
	char	*last;

	while (token && token[++i])
	{
		if (is_expand(&token[i]))
		{
			first = ft_substr(token, 0, i);
			if (ft_strlen(first) != ((size_t)i))
				malloc_fail(data);
			expand = get_expand(&token[i], type, data);
			i += (get_expand_key_len(&token[i]) + 1);
			last = ft_strdup(&token[i]);
			if (!last)
			{
				free_expand_buffer(first, expand, last);
				malloc_fail(data);
			}
			free(token);
			token = concatenate_expand(first, expand, last, data);
			i = -1;
		}
	}
	return (token);
}

void	expand_var(t_token **token_lst, t_data *data)
{
	t_token	*node;
	t_token	*next;

	node = *token_lst;
	while (node)
	{
		next = node->next;
		node->tmp = NULL;
		if (node->content && node->type != QUOTE_S)
		{
			node->tmp = ft_strdup(node->content);
			if (!node->tmp)
				malloc_fail(data);
			node->content = handle_expand(node->content, -1, node->type, data);
			if (!node->content[0] && is_a_target_redir(node)
				&& node->type != QUOTE_D)
				node->type = REDIR_AMBIGUOUS;
			else if (!node->content[0] && node->type != QUOTE_D)
				remove_node(node, data);
			else if (node->type == QUOTE_D)
				node->type = WORD;
		}
		node = next;
	}
}
