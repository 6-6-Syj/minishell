/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:36:27 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:23 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i])
	{
		while (little[j] && (little[j] == big[i + j]))
			j++;
		if ((little[j] == '\0') && (i + j <= len))
			return ((char *)&big[i]);
		j = 0;
		i++;
	}
	return (NULL);
}
/*
#include <bsd/string.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s1[] = "Bonjour la";
	char	s2[] = "jou";

	printf("strnstr = %s\n", strnstr(s1, s2, 2));
	printf("ft_strnstr = %s\n", ft_strnstr(s1, s2, 2));
	return (0);
}
*/