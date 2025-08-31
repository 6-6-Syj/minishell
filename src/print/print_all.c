/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:17:33 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/06/26 16:31:22 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all(t_data *data)
{
	ft_printf("\n");
	print_token_lst(data->token);
	ft_printf("\033[0;34m\033[1m ECHO $?: %d\033[0m\n", data->err);
}
