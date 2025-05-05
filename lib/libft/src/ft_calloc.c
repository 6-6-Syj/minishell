/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:10:47 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:31:34 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buff;

	if (!nmemb || !size)
		return (malloc(0));
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	buff = malloc(size * nmemb);
	if (!buff)
		return (NULL);
	ft_bzero(buff, size * nmemb);
	return (buff);
}
/*
int	main(void)
{
	int	*tab;
	int	i;

	i = 0;
	tab = ft_calloc(99999999999999, 0);
	while (i < 10)
	{
		printf("%i\n", tab[i]);
		i++;
	}
	return (0);
}
*/