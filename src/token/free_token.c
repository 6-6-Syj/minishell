/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:19:51 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 20:19:51 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

void	free_token_node(t_token *token_node)
{
	if (token_node && token_node->content)
	{
		free(token_node->content);
		token_node->content = NULL;
	}
	if (token_node)
	{
		free(token_node);
		token_node = NULL;
	}
}

void	free_token_lst(t_token **token_lst)
{
	t_token	*current;
	t_token	*tmp;

	if (!*token_lst)
		return ;
	current = *token_lst;
	while (current)
	{
		tmp = current->next;
		if (current)
			free_token_node(current);
		current = tmp;
	}
}
