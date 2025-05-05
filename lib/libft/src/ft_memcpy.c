/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:34:40 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:32:27 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*src_tmp;
	unsigned char	*dst_tmp;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	src_tmp = (unsigned char *)src;
	dst_tmp = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dst_tmp);
}
/*
#include <string.h>

int	main(void)
{
	int	src[7] = {1, 2, 3, 4, 5, 6, 7};
	int	i;

	//int	dst[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	i = 0;
	ft_memcpy(src + 2, src, sizeof(int) * 4);
	// memcpy(src + 2, src, sizeof(int) * 4);
	while (i < 7)
	{
		printf("src = %i\n", src[i]);
		i++;
	}
	i = 0;
	while (i < 7)
	{
		printf("dst = %i\n", dst[i]);
		i++;
	}
	return (0);
}
*/