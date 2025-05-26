/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:17:27 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 20:17:27 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	init_data(t_data *data)
{
	data->ast = NULL;
	data->cmds = NULL;
	data->env = NULL;
	data->token = NULL;
	data->err = 0;
	data->err_msg = NULL;
	data->cmds = NULL;
	data->env = NULL;
	data->token = NULL;
	data->ast = NULL;
}
