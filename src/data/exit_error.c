/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:40 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/18 23:47:13 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data)
{
	int	err;

	err = 0;
	if (data)
	{
		if (data->err_msg)
		{
			ft_putstr_fd(data->err_msg, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		err = data->err;
		free_data(data);
	}
	exit(err);
}
