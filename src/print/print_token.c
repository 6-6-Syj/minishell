/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:46:36 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/08 17:48:04 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(t_type type)
{
	if (type == TYPE_PAREN_L)
		ft_printf(MGT"\t--->   PAREN_L\t\n"RST);
	else if (type == TYPE_PAREN_R)
		ft_printf(MGT"\t--->   PAREN_R\t\n"RST);
	else if (type == TYPE_REDIR_IN)
		ft_printf(MGT"\t--->   REDIR_IN\t\n"RST);
	else if (type == TYPE_HERE_DOC)
		ft_printf(MGT"\t--->   HERE_DOC\t\n"RST);
	else if (type == TYPE_REDIR_OUT)
		ft_printf(MGT"\t--->   REDIR_OUT\t\n"RST);
	else if (type == TYPE_REDIR_APPEND)
		ft_printf(MGT"\t--->   REDIR_APPEND\t\n"RST);
	else if (type == TYPE_PIPE)
		ft_printf(MGT"\t--->   PIPE\t\n"RST);
	else if (type == TYPE_AND)
		ft_printf(MGT"\t--->   AND\t\n"RST);	
	else if (type == TYPE_OR)
		ft_printf(MGT"\t--->   OR\t\n"RST);
	else if (type == TYPE_QUOTE_S)
		ft_printf(MGT"\t--->   QUOTE_S\t\n"RST);
	else if (type == TYPE_QUOTE_D)
		ft_printf(MGT"\t--->   QUOTE_D\t\n"RST);
	else if (type == TYPE_SPACE)
		ft_printf(MGT"\t--->   SPACE\t\n"RST);
	else if (type == TYPE_WORD)
		ft_printf(MGT"\t--->   WORD\t\n"RST);
	else if (type == TYPE_UNKNOWN)
		ft_printf(MGT"\t--->   UNKNOWN\t\n"RST);
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

	ft_printf("+-----------------------+\n");
	ft_printf("|  TOKEN LST            |\n");
	ft_printf("+-----------------------+\n");
	token = token_list;
	i = 0;
	while (token)
	{
		print_token(token, i);
		token = token->next;
		i++;
	}
	ft_printf("\n");
}
