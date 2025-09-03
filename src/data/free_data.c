/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/09/02 19:21:38 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/09/02 19:21:38 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "data.h"
#include "env.h"
#include "token.h"

void	free_data(t_data *data)
{
	if (data->token)
	{
		free_token_lst(&data->token);
		data->token = NULL;
	}
	if (data->env)
	{
		free_env_lst(&data->env);
		data->env = NULL;
	}
	if (data->ast)
	{
		free_ast(&data->ast);
		data->ast = NULL;
	}
	if (data->env_tab)
	{
		free_env_tab(data);
		data->env = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
}

void	free_tmp_data(t_data *data)
{
	if (data)
	{
		if (data->token)
		{
			free_token_lst(&data->token);
			data->token = NULL;
		}
		if (data->ast)
		{
			free_ast(&data->ast);
			data->ast = NULL;
		}
		if (data->input)
		{
			free(data->input);
			data->input = NULL;
		}
	}
}
