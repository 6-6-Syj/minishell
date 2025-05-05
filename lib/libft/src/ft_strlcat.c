/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:34:08 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:08 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	dst_len = 0;
	src_len = (ft_strlen(src));
	while (dst_len < size && dst[dst_len])
		dst_len++;
	if (dst_len == size)
		return (src_len + size);
	if (size > (src_len + dst_len))
		dst = ft_strcat(dst, src);
	if (size <= (src_len + dst_len))
		dst = ft_strncat(dst, src, size - dst_len - 1);
	return (src_len + dst_len);
}
/*
#include <bsd/string.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	ft_src[] = "maison";
	char	ft_dest[] = "cata";
	char	src[] = "maison";
	char	dst[] = "cata";

	printf("ft_len = %zu\n", ft_strlcat(ft_dest, ft_src, 6));
	printf("ft_strlcat = %s\n\n", ft_dest);
	printf("len = %zu\n", strlcat(dst, src, 6));
	printf("strlcat = %s\n\n", dst);
	return (0);
}
*/