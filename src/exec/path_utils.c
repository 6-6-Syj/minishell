/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-19 18:09:10 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-19 18:09:10 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

int	is_absolute_or_relative_path(char *cmd)
{
	return (cmd[0] == '/' || !ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd,
			"../", 3));
}
