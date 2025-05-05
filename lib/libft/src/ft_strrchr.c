/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:36:35 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:26 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	c_tmp;
	int				i;

	if (!str)
		return (NULL);
	c_tmp = (unsigned char)c;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c_tmp)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "salut le monde";

	printf("ft_strrchr = %s\n", ft_strrchr(str, 'l'));
	printf("strrchr = %s\n", strrchr(str, 'l'));
}
*/