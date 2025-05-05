/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:34:24 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:00 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (!src)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
int	main(void)
{
	char	src[] = "salut";
	char	*dst;
	char	*dst_ft;

	dst = strdup(src);
	printf("strdup = %s\n", dst);
	dst_ft = ft_strdup(src);
	printf("ft_strdup = %s\n", dst);
	return (0);
}
*/