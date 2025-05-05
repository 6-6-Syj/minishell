/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:31:24 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:32:18 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
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
	printf("size list = %i\n", ft_lstsize(lst));
	return (0);
}
*/