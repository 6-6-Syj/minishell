/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:38:19 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/27 14:10:29 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}
/*
#include <stdio.h>
#include <limits.h>
int	main(void)
{
	printf("ft_atoi = %'i\n", ft_atoi("-9223372036854775819"));
	perror("ft_atoi");
	printf("\natoi = %i\n", atoi("-9223372036854775819"));
	perror("atoi");
	
	
	//if (res >= LONG_MAX / 10 && sign == 1)
	//		return (-1);
	//else if (res >= LONG_MAX / 10 && sign == -1)
	//		return (0);
	return (0);
	
}
*/