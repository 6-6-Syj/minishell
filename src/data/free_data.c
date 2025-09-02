/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:21:38 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 19:21:38 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "token.h"
#include "env.h"
#include "ast.h"

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->token)
			free_token_lst(&data->token);
		if (data->env)
			free_env_lst(&data->env);
		if (data->ast)
			free_ast(&data->ast);
		if (data->env_tab)
			free_env_tab(data);
		if (data->input)
			free(data->input);
	}
}

void	free_tmp_data(t_data *data)
{
	if (data)
	{
		if (data->token)
			free_token_lst(&data->token);
		if (data->ast)
			free_ast(&data->ast);
	}
}
