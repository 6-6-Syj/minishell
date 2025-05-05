/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:18:01 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:31:52 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static int	len_nb(long int nb)
{
	int	nb_of_digits;

	nb_of_digits = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb_of_digits++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		nb_of_digits++;
	}
	return (nb_of_digits);
}

char	*ft_itoa(int n)
{
	char		*res;
	bool		neg;
	long int	nb;
	size_t		len;

	neg = false;
	nb = (long int)n;
	len = len_nb(nb);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (nb < 0)
	{
		neg = true;
		nb *= -1;
	}
	while (len > 0)
	{
		res[len - 1] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	if (neg == true)
		res[0] = '-';
	return (res);
}
/*
int	main(void)
{
	printf("ft_itoa = %s\n", ft_itoa(9));
	printf("itoa = %s\n", itoa(9));	
	return (0);
}
*/