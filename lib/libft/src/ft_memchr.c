/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:40:50 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:32:22 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_tmp;
	unsigned char	c_tmp;
	size_t			i;

	s_tmp = (unsigned char *)s;
	c_tmp = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s_tmp[i] == c_tmp)
			return ((void *)&s_tmp[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*ft_src;
	char	*src;

	ft_src = "salut";
	src = "salut";
	printf("ft_memchr = %s\n", (char *)ft_memchr(src, 'u', 6));
	printf("mem_chr = %s\n", (char *)memchr(src, 'u', 6));
	return (0);
}
*/