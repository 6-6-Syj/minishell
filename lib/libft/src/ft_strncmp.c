/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:35:03 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:21 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;
	size_t			i;

	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (-1);
	while ((s1_tmp[i] || s2_tmp[i]) && i < n)
	{
		if (s1_tmp[i] != s2_tmp[i])
			return (s1_tmp[i] - s2_tmp[i]);
		i++;
	}
	return (0);
}
/*
#include <bsd/string.h>

int	main(void)
{
	char	s1[] = "Salut mec ca va";
	char	s2[] = "Salut";

	printf("ft_strncmp = %i\n", ft_strncmp(s1, s2, 8));
	printf("strncmp = %i\n", strncmp(s1, s2, 8));
	return (0);
}
*/