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

#include "data.h"
#include <unistd.h>

void	init_data(t_data *data)
{
	data->err = 0;
	data->err_msg = NULL;
}

void	init_all(t_data *data, char *input)
{
	init_data(data);
	init_token(data->token, input);
}
