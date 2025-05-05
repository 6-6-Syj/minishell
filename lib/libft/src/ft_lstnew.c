/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/20 11:36:55 by aviscogl          #+#    #+#             */
/*   Updated: 2024/11/20 11:36:55 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *new_content)
{
	t_list	*new_node;

	if (!new_content)
		new_content = NULL;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = new_content;
	new_node->next = NULL;
	return (new_node);
}
