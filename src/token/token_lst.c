/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:08:01 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/08 20:08:01 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "unistd.h"
#include "libft.h"

t_token	*get_last_token(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_token	*add_token_node(t_token **token_lst)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL); // TODO: MALLOC ERROR
	if (!*token_lst)
	{
		*token_lst = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last_node = get_last_token(*token_lst);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
	return (new_node);
}