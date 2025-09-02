/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:49:54 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 16:15:21 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft.h"
#include "print.h"

static void	remove_quote(char **token_content, t_data *data)
{
	char	*buff;
	int		len;

	len = ft_strlen(*token_content);
	if (len == 2)
		buff = ft_calloc(1, 1);
	else
		buff = ft_substr(*token_content, 1, len - 2);
	if (!buff)
		malloc_fail(data);
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
			remove_quote(&current->content, data);
			current->type = WORD;
		}
		current = current->next;
	}
}

void	remove_double_quote(t_token **token_lst, t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	current = *token_lst;
	while (current)
	{
		tmp = current->next;
		if (current->type == QUOTE_D)
			remove_quote(&current->content, data);
		current = tmp;
	}
}
