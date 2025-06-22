/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-03 18:04:05 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-03 18:04:05 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	parse_echo(char **args, int *i)
{
	int	newline;
	int	j;

	newline = true;
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 2;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
		{
			newline = false;
			(*i)++;
		}
		else
			break ;
	}
	return (newline);
}

int	ft_echo(t_command *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (cmd->args[i])
		newline = parse_echo(cmd->args, &i);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
