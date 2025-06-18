/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:46:36 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/27 18:49:15 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(t_type type)
{
	if (type == PAREN_L)
		ft_printf(MGT "\t--->   PAREN_L\t" RST);
	else if (type == PAREN_R)
		ft_printf(MGT "\t--->   PAREN_R\t" RST);
	else if (type == REDIR_IN)
		ft_printf(MGT "\t--->   REDIR_IN\t" RST);
	else if (type == HERE_DOC)
		ft_printf(MGT "\t--->   HERE_DOC\t" RST);
	else if (type == REDIR_OUT)
		ft_printf(MGT "\t--->   REDIR_OUT\t" RST);
	else if (type == REDIR_APPEND)
		ft_printf(MGT "\t--->   REDIR_APPEND\t" RST);
	else if (type == PIPE)
		ft_printf(MGT "\t--->   PIPE\t" RST);
	else if (type == AND)
		ft_printf(MGT "\t--->   AND\t" RST);
	else if (type == OR)
		ft_printf(MGT "\t--->   OR\t" RST);
	else if (type == QUOTE_S)
		ft_printf(MGT "\t--->   QUOTE_S\t" RST);
	else if (type == QUOTE_D)
		ft_printf(MGT "\t--->   QUOTE_D\t" RST);
	else if (type == SPACE)
		ft_printf(MGT "\t--->   SPACE\t" RST);
	else if (type == EXPAND)
		ft_printf(MGT "\t--->   EXPAND\t" RST);
	else if (type == WORD)
		ft_printf(MGT "\t--->   WORD\t" RST);
	else if (type == CMD)
		ft_printf(MGT "\t--->   CMD\t" RST);
	else if (type == ARG)
		ft_printf(MGT "\t--->   ARG\t" RST);
	else if (type == EXPAND)
		ft_printf(MGT "\t--->   EXPAND\t" RST);
	else if (type == VAR)
		ft_printf(MGT "\t--->   VAR\t" RST);
	else if (type == REDIR_TARGET)
		ft_printf(MGT "\t--->   FILE\t" RST);
	else if (type == UNKNOWN)
		ft_printf(MGT "\t--->   UNKNOWN\t" RST);
}

void	print_token(t_token *token, int i)
{
	if (token->content)
	{
		if (i > 0)
			ft_printf(B " |\n |\n V\n" RST, i);
		ft_printf(G "[%s]" RST, token->content);
		print_token_type(token->type);
		ft_printf(R"  (%d)"RST, token->priority);
		ft_printf("\n");
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
