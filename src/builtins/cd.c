/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:04 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:10:20 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
	ERRORS FROM CHDIR:

	● EACCES (13): Permission denied to access the specified directory.

	● ENOENT (2): The specified directory does not exist.

	● ENOTDIR (20): Part of the specified path is not a directory.
*/

static int	ft_cd(char *path)
{
	ft_printf("PATH=%s\n", path);
	if (chdir(path) == -1)
	{
		ft_printf("ERROR\n");
		free(path);
		return (1); // TODO: HANDLE ERRORS CODE
	}
	else
	{
		free(path);
		return (NO_ERROR);
	}
}

int	handle_cd(t_env *env, char *input)
{
	char	*path;
	int		len;
	int		i;

	(void)env;
	i = 0;
	while (input[i] == ' ')
		i++;
	i += 3; // Exclude "cd"
	while (input[i] == ' ')
		i++;
	len = ft_strlen(input - i);
	path = malloc(len + 1);
	if (!path)
		return (-42); // TODO: MALLOC ERROR
	ft_strcpy(path, input); // maybe use strlcpy ? 
	return (ft_cd(path));
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
