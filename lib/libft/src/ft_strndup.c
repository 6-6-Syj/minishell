/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:47:31 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 03:38:29 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dst;

	if (!src || n <= 0)
		return (NULL);
	i = 0;
	dst = malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (NULL);
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
