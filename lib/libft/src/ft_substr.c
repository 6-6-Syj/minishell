/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:36:50 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:31 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(src))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(src) - start)
		len = ft_strlen(src) - start;
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = src[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
int	main(void)
{
	char	*dst;

	dst = ft_substr("hello world", 33, 2);
	printf("%src", dst);
	return (0);
}
*/