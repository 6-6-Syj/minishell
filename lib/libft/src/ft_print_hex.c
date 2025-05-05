/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:40:11 by dabuchhe          #+#    #+#             */
/*   Updated: 2024/12/09 16:40:11 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_nb_hex(unsigned long nb)
{
	int	nb_of_digits;

	nb_of_digits = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		nb_of_digits++;
	}
	return (nb_of_digits);
}

void	ft_putnbr_ui(unsigned int ptr, char *base)
{
	if (ptr >= 16)
	{
		ft_putnbr_ui(ptr / 16, base);
		ft_putnbr_ui(ptr % 16, base);
	}
	else
		ft_putchar(base[ptr]);
}

void	ft_putnbr_ul(unsigned long ptr)
{
	char	*base;

	base = "0123456789abcdef";
	if (ptr >= 16)
	{
		ft_putnbr_ul(ptr / 16);
		ft_putnbr_ul(ptr % 16);
	}
	else
		ft_putchar(base[ptr]);
}

size_t	ft_print_hex(unsigned int nb, const char format)
{
	if (format == 'x')
		ft_putnbr_ui(nb, "0123456789abcdef");
	else if (format == 'X')
		ft_putnbr_ui(nb, "0123456789ABCDEF");
	return (ft_len_nb_hex(nb));
}

size_t	ft_print_memory(unsigned long ptr)
{
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	ft_putnbr_ul(ptr);
	return (ft_len_nb_hex(ptr) + 2);
}
