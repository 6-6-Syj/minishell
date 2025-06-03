/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:04 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:50:38 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

/*
	ERRORS FROM CHDIR:

	● EACCES (13): Permission denied to access the specified directory.

	● ENOENT (2): The specified directory does not exist.

	● ENOTDIR (20): Part of the specified path is not a directory.
*/

int	ft_cd(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd && cmd->args[i])
		i++;
	// TODO: CHECK
	// cd /hwffewefwef | sleep 5 | ls | cat -e (not working)
	if (i > 2 || chdir(cmd->args[1]) == -1)
	{
		if (i > 2)
			ft_printf("cd: too many arguments\n");
		else
			ft_printf("cd: %s: No such file or directory\n", cmd->args[1]);
		data->err = 1;
		return (1);
	}
	else
	{
		data->err = 0;
		return (NO_ERROR);
	}
}

// TODO: HANDLE CD WITH NO ARG ?

/*

/home/jmagand/bin
/home/jmagand/bin
/usr/local/sbin
/usr/local/bin
/usr/sbin
/usr/bin
/sbin
/bin
/usr/games
/usr/local/games
/snap/bin
/home/jmagand/.dotnet/tools

*/
