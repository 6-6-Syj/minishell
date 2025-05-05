/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:19:42 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/24 16:22:50 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	c_tmp;

	c_tmp = (unsigned char)c;
	while (*str)
	{
		if (*str == c_tmp)
			return ((char *)str);
		str++;
	}
	if (c_tmp == '\0')
		return ((char *)str);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "salut le monde";

	printf("ft_strchr = %s\n", ft_strchr(str, 'l'));
	printf("strchr = %s\n", strchr(str, 'l'));
}
*/