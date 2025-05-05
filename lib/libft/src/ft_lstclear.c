/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/22 14:36:39 by dabuchhe          #+#    #+#             */
/*   Updated: 2024/11/22 14:36:39 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (*lst != NULL)
	{
		tmp = tmp->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
