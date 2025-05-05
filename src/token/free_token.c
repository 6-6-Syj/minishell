/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:19:51 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 20:19:51 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (token)
	{
		tmp = token->next;
		if (token->content)
			free(token->content);
		free(token);
		token = tmp;
	}
}
