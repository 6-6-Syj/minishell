/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:31:17 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:31:32 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int	main(void)
{
	int	tab[] = {10, 45, 88, 12, 24};
	int	i;

	i = 0;
	while (i < 5)
	{
		bzero(&tab[i], sizeof(int));
		printf("bzero = %i\n", tab[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		ft_bzero(&tab[i], sizeof(int));
		printf("ft_bzero = %i\n", tab[i]);
		i++;
	}
	return (0);
}
*/