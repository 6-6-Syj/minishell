/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:17:33 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/28 18:00:12 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all(t_data *data)
{
	ft_printf("\n");
	// print_token_lst(data->token);
	// print_ast_graphical(data->ast);
	ft_printf("CODE_$?: %d\n", data->err);
	// print_data(data);
}
