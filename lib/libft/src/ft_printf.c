/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:40:25 by dabuchhe          #+#    #+#             */
/*   Updated: 2024/12/09 16:40:25 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_print_format(va_list arg, const char format)
{
	size_t	len_arg;

	len_arg = 0;
	if (format == '%')
		len_arg += ft_print_char('%');
	else if (format == 'c')
		len_arg += ft_print_char(va_arg(arg, int));
	else if (format == 's')
		len_arg += ft_print_string(va_arg(arg, char *));
	else if (format == 'p')
		len_arg += ft_print_memory(va_arg(arg, unsigned long));
	else if (format == 'd')
		len_arg += ft_print_int(va_arg(arg, int));
	else if (format == 'i')
		len_arg += ft_print_int(va_arg(arg, int));
	else if (format == 'u')
		len_arg += ft_print_unsigned_int(va_arg(arg, unsigned int));
	else if (format == 'x')
		len_arg += ft_print_hex(va_arg(arg, unsigned int), format);
	else if (format == 'X')
		len_arg += ft_print_hex(va_arg(arg, unsigned int), format);
	return (len_arg);
}

size_t	ft_printf(const char *str, ...)
{
	va_list	arg;
	size_t	len_print;
	size_t	i;

	i = 0;
	len_print = 0;
	va_start(arg, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len_print += ft_print_format(arg, str[i + 1]);
			i++;
		}
		else
			len_print += ft_print_char(str[i]);
		i++;
	}
	va_end(arg);
	return (len_print);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	c = 'A';
// 	char	str[] = "salut";
// 	void	*ptr;
// 	int		nb;
// 	unsigned int		u_nb;
// 	long int	long_nb;
// 	long long int	long_long_nb;

// 	nb = -12345;
// 	u_nb = -1;
// 	long_nb = 999999999;
// 	long_long_nb = 999999999999;

// 	ft_printf("return (ft_printf = %d\n", ft_printf("c = %c", c)));
// 	printf("return (printf = %d\n\n", printf("c = %c", c)));

// 	ft_printf("return (ft_printf = %d\n", ft_printf("s = %s\n", str)));
// 	printf("return (printf = %d\n\n", printf("s = %s\n", str)));

// 	ft_printf("return (ft_printf = %d\n", ft_printf("p = %p\n", ptr)));
// 	printf("return (printf = %d\n\n", printf("p = %p\n", ptr)));

// 	ft_printf("return (ft_printf = %d\n", ft_printf("d = %d\n", nb)));
// 	printf("return (printf = %d\n\n", printf("d = %d\n", nb)));

// 	ft_printf("return (ft_printf = %d\n", ft_printf("i = %i\n", nb)));
// 	printf("return (printf = %d\n\n", printf("i = %i\n", nb)));

// 	ft_printf("return (ft_printf = %d\n", ft_printf("u = %u\n", u_nb)));
// 	printf("return (printf = %d\n\n", printf("u = %u\n", u_nb)));

// 	ft_printf("return (ft_printf = %d\n", ft_printf("x = %x\n", u_nb)));
// 	printf("return (printf = %d\n\n", printf("x = %x\n", u_nb)));

// 	ft_printf("return (ft_printf = %d\n", ft_printf("X = %X\n", u_nb)));
// 	printf("return (printf = %d\n\n", printf("X = %X\n", u_nb)));
// 	return(0);
// }