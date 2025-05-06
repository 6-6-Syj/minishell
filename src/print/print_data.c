/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:45:44 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/06 18:21:09 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	print_data(t_data *data)
{
	ft_printf("data.err =\t%d\n", data->err);
	ft_printf("data.err_msg =\t%s\n\n", data->err_msg);
}
