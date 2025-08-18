/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:04:05 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/18 23:07:20 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "print.h"

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

static bool	handle_echo_no_arg(t_command *cmd)
{
	if (!cmd->args[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (true);
	}
	return (false);
}

/*
if (is_special_case(ft_strtrim(cmd->args[1], " ")))
	still reachable echo ''''''''''$USER''''''''''
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		if (newline)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
		}
*/
static bool	handle_echo_special_case(t_command *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->args[1][i])
	{
		if (cmd->args[1][i] == '-')
			count++;
		if (cmd->args[1][i] != '-' && cmd->args[1][i] != ' ')
			return (false);
		if (cmd->args[1][i] == ' ')
			i++;
		else
			i++;
	}
	if (count == 1)
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (true);
	}
	return (false);
}

int	ft_echo(t_command *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (cmd->args[i])
		newline = parse_echo(cmd->args, &i);
	if (handle_echo_no_arg(cmd))
		return (0);
	if (handle_echo_special_case(cmd))
		return (0);
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
