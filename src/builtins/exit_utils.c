/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-03 21:10:28 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-03 21:10:28 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>

static long long	handle_overflow(int sign)
{
	if (sign == 1)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

static void	parse_sign_whitespace(const char *str, int *i, int *sign)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

long long	ft_atoll_shell(const char *str)
{
	long long	nb;
	int			i;
	int			sign;
	int			digit;

	nb = 0;
	i = 0;
	sign = 1;
	parse_sign_whitespace(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (LLONG_MAX / 10))
			return (handle_overflow(sign));
		nb *= 10;
		digit = str[i] - '0';
		if (nb > (LLONG_MAX - digit))
			return (handle_overflow(sign));
		nb += digit;
		i++;
	}
	return (nb * sign);
}
