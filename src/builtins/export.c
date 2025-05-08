/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:22:44 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:13:52 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// 1 failure: Some rare cases.	ex:
// not enough memory or fd is full

int	ft_export(t_env **head, char **args, int i)
{

}

int	handle_export(t_env **env_lst, char *input)
{
	char	**args;
	int		i;
	int		res;

	res = 0;
	i = 0;
	args = ft_split(input, ' ');
	{
		// TODO: print_env
		return (NO_ERROR);
	}
	while (args[++i])
		ft_export(env_lst, args, i);
	while (args && args[i])
		free(args[i++]);
	free(args);
	return (0);
}
