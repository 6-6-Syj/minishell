/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:40 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 02:20:48 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "libft.h"

void	exit_error(t_data *data)
{
	free_data(data);
	if (data->err)
	{
		ft_printf("Error\n");
		ft_printf("%s\n", data->err_msg);
	}
	exit(data->err);
}
