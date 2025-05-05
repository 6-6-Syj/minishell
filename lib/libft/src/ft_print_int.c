/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:40:19 by dabuchhe          #+#    #+#             */
/*   Updated: 2024/12/09 16:40:19 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_nb(long int nb)
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

void	ft_putnbr(long int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

size_t	ft_print_int(int nb)
{
	ft_putnbr((long int)nb);
	return (ft_len_nb((long int)nb));
}

size_t	ft_print_unsigned_int(unsigned int nb)
{
	ft_putnbr((long int)nb);
	return (ft_len_nb((long int)nb));
}
