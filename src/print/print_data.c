/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:45:44 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/07 07:02:51 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	print_data(t_data *data)
{
	ft_printf("+-----------------------+\n");
	ft_printf("|  DATA                 |\n");
	ft_printf("+-----------------------+\n");
	ft_printf(" data.err\t= %d\n", data->err);
	ft_printf(" data.err_msg\t= %s\n", data->err_msg);
	ft_printf("\n");
}
