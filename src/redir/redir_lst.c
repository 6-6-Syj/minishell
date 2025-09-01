/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-31 19:00:43 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-31 19:00:43 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "unistd.h"
#include "libft.h"

t_redir	*get_first_redir_node(t_redir *current)
{
	if (!current)
		return (NULL);
	while (current->prev != NULL)
		current = current->prev;
	return (current);
}

t_redir	*get_last_redir_node(t_redir *current)
{
	if (!current)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

t_redir	*add_redir_node(t_redir **redir_lst)
{
	t_redir	*new_node;
	t_redir	*last_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
		return (NULL);
	if (!*redir_lst)
	{
		*redir_lst = new_node;
		new_node->next = NULL;
	}
	else
	{
		last_node = get_last_redir_node(*redir_lst);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
	return (new_node);
}
