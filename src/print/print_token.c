/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:46:36 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 22:19:17 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	print_token(t_token *token_list)
{
	t_token	*token;
	int		i;

	token = token_list;
	i = 0;
	while (token)
	{
		if (token->content)
			ft_printf("token[%d]\t= \n", i, token->content);
		token = token->next;
		i++;
	}
}
