/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:34:43 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:32:32 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_tmp;
	unsigned char	c_tmp;
	size_t			i;

	s_tmp = (unsigned char *)s;
	c_tmp = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		s_tmp[i] = c_tmp;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	int	tab[5] = {10, 45, 88, 12, 24};
	int	i;

	i = 0;
	memset(tab, 0, (sizeof(int) * 5));
	while (i < 5)
	{
		printf("memset = %i\n", tab[i]);
		i++;
	}
	ft_memset(tab, 0, (sizeof(int) * 5));
	i = 0;
	while (i < 5)
	{
		printf("ft_memset = %i\n", tab[i]);
		i++;
	}
	return (0);
}
*/