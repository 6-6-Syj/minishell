/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:20:15 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:05 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (s1 && s1[i])
		dst[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		dst[j++] = s2[i++];
	dst[j] = '\0';
	return (dst);
}
/*
int	main(void)
{
	char	s1[] = "salut";
	char	s2[] = "ca va";
	char	*dst;

	dst = ft_strjoin(s1, s2);
	printf("dst = %s\n", dst);
	return (0);
}
*/