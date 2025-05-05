/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:31:38 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/17 03:31:29 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *str)
{
	int			i;
	int			neg;
	long long	out;

	out = 0;
	i = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		out *= 10;
		out += str[i] - 48;
		i++;
	}
	out *= neg;
	return (out);
}
