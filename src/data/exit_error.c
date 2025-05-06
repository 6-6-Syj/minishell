/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:40 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/06 03:11:25 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
