/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:31:07 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:32:08 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list	lst1;
	t_list	lst2;
	t_list	lst3;
	t_list	*lst;

	lst = &lst1;
	lst1.next = &lst2;
	lst2.next = &lst3;
	lst3.next = NULL;
	lst1.content = "list 1";
	lst2.content = "list 2";
	lst3.content = "list 3";
	lst = ft_lstlast(lst);
	printf("last node = %s\n", (char *)lst->content);
	return (0);
}
*/