/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:37:23 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:14:55 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

// TODO: Error if directory is inaccessible, or deleted...
int	ft_pwd(t_data *data)
{
	char	res[PATH_MAX];

	if (getcwd(res, PATH_MAX))
	{
		ft_putstr_fd(res, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		data->err = 0;
		return (0);
	}
	else
	{
		// CHECK THIS
		data->err = 1;
		return (1);
	}
}
