/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:49:11 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/04 19:11:38 by dabuchhe         ###   ########lyon.fr   */
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
char	*handle_expand(char *token, int i, t_data *data)
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
			i = -1;
		}
	}
	return (token);
}

static void	print_ambiguous_redir(t_token *token)
{
	token->type = REDIR_AMBIGUOUS;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token->tmp, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

void	expand_var(t_token **token_lst, t_data *data)
{
	t_token	*current;
	t_token	*next;
	
	current = *token_lst;
	while (current)
	{
		next = current->next;
		current->tmp = NULL;
		if (current->content && current->type != QUOTE_S)
		{
			current->tmp = ft_strdup(current->content);
			if (!current->tmp)
				malloc_fail(data);
			current->content = handle_expand(current->content, -1, data);
			if (!current->content[0] && is_a_target_redir(current) && current->type != QUOTE_D)
				print_ambiguous_redir(current);
			else if (!current->content[0] && current->type != QUOTE_D)
				remove_node(current, data);
			else if (current->type == QUOTE_D)
				current->type = WORD;
		}
		current = next;
	}
}
