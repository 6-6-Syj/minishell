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
/*   Created: 2025/05/05 20:17:03 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 20:17:03 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_data(t_data *data)
{
	if (data->token)
		free_token_lst(&data->token);
	// free_env_lst(&data->env);
}
