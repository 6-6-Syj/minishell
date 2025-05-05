/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:36:42 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:33:29 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(str);
	if (!str)
		return (NULL);
	while (ft_strchr(set, str[start]))
		start++;
	while (ft_strchr(set, str[end]))
		end--;
	if (start > end)
		return (ft_calloc(1, 1));
	return (ft_substr(str, start, (end - start) + 1));
}
/*
int	main(int ac, char **av)
{
	printf("dst = %s\n",ft_strtrim(av[1], av[2]));
	return (0);
}
*/