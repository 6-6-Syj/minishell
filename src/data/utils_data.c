/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-24 20:29:40 by jmagand           #+#    #+#             */
/*   Updated: 2025-07-24 20:29:40 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	update_shlvl(t_data *data)
{
	char	*shlvl_str;
	int		shlvl_int;

	shlvl_str = NULL;
	if (isatty(STDIN_FILENO))
		shlvl_str = get_env_var(data, "SHLVL");
	if (shlvl_str)
	{
		shlvl_int = ft_atoi(shlvl_str);
		shlvl_int++;
		shlvl_str = ft_itoa(shlvl_int);
		set_env_var(data, "SHLVL", shlvl_str);
		free(shlvl_str); // LEAKS
	}
}
