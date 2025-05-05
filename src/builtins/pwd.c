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

// TODO: Handle error code enum
int	ft_pwd(void)
{
	char	res[PATH_MAX];

	if (getcwd(res, PATH_MAX))
	{
		ft_putstr_fd(res, 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	else
		return (1);
}
