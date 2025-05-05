/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:35:34 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:32:29 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;

	if (!dst && !src)
		return (NULL);
	tmp_dest = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (dst > src)
		while (0 < n--)
			tmp_dest[n] = tmp_src[n];
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
/*
#include <string.h>

int	main(void)
{
	int	src[5] = {1, 2, 3, 4, 5};
	int	dst[6] = {0, 0, 0, 0, 0, 0};
	int	i;

	i = 0;
	ft_memmove(src + 2, src, sizeof(int) * 1);;
	while (i < 5)
	{
		printf("src = %i\n", src[i]);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		printf("dst = %i\n", dst[i]);
		i++;
	}
	printf("void = %p\n", (void *)dst);
	printf("void = %p\n", (void *)src);
	return (0);
}
*/