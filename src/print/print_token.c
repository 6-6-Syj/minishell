/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:46:36 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/06 05:51:56 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(t_type type)
{
	if (type == TYPE_QUOTE_S)
		ft_printf(MGT"\t--->   QUOTE_S\t\n"RST);
	else if (type == TYPE_QUOTE_D)
		ft_printf(MGT"\t--->   QUOTE_D\t\n"RST);
	else if (type == TYPE_SPACE)
		ft_printf(MGT"\t--->   SPACE\t\n"RST);
	else
		ft_printf(MGT"\t--->   WORD\t\n"RST);
		
}

void	print_token(t_token *token, int i)
{
	if (token->content)
	{
		if (i > 0)			
			ft_printf(B" |\n |\n V\n"RST, i);
		ft_printf(G"[%s]"RST, token->content);
		print_token_type(token->type);
	}
}

void	print_token_lst(t_token *token_list)
{
	t_token	*token;
	int		i;

	token = token_list;
	i = 0;
	while (token)
	{
		print_token(token, i);
		token = token->next;
		i++;
	}
}
