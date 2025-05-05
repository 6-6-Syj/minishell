/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/22 14:35:39 by dabuchhe          #+#    #+#             */
/*   Updated: 2024/11/22 14:35:39 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	new_node->next = *lst;
	*lst = new_node;
}
/*
int	main(void)
{
	t_list *alst;

	alst = ft_lstnew_node((void *)" les copains");
	ft_lstadd_front(&alst, ft_lstnew_node((void *)"Salut"));
	printf("%s\n", (char *)(alst)->content);
}
*/