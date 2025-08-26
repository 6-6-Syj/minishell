/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:29:40 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/26 21:03:49 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <libft.h>

void	update_shlvl(t_data *data)
{
	char	shlvl_stack[PATH_MAX];
	char	*shlvl_str;
	int		shlvl_int;

	shlvl_str = NULL;
	if (isatty(STDIN_FILENO))
		shlvl_str = get_env_var(data, "SHLVL");
	if (shlvl_str)
	{
		shlvl_int = ft_atoi(shlvl_str);
		shlvl_int++;
		free(shlvl_str);
		shlvl_str = ft_itoa(shlvl_int);
		ft_strcpy(shlvl_stack, shlvl_str);
		free(shlvl_str);
		set_env_var(data, "SHLVL", shlvl_stack);
	}
}
