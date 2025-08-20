/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:48:21 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/08/20 16:48:38 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_count(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == CMD)
			count++;
		token = token->next;
	}
	return (count);
}
