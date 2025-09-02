/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:24:54 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/05 20:13:36 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "data.h"
#include "libft.h"

static bool	is_valid_number(char *str, bool *minus)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (false);
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			*minus = true;
		i++;
	}
	else
		*minus = false;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	if (i > (*minus))
		return (true);
	else
		return (false);
}

static bool	handle_first_arg(t_command *cmd, int *exit_code)
{
	long long	num;
	bool		minus;

	num = 0;
	minus = false;
	if (is_valid_number(cmd->args[1], &minus))
	{
		num = ft_atoll_shell(cmd->args[1]);
		*exit_code = (int)(num % 256);
		if (*exit_code < 0)
			*exit_code += 256;
		ft_putstr_fd("exit\n", STDERR_FILENO);
		return (false);
	}
	else
	{
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		*exit_code = 2;
		return (true);
	}
}

int	ft_exit(t_command *cmd, t_data *data)
{
	int		exit_code;
	bool	should_exit;

	exit_code = 0;
	should_exit = false;
	if (!cmd->args[1])
	{
		exit_code = data->exit_err;
		ft_putstr_fd("exit\n", STDERR_FILENO);
	}
	else
	{
		should_exit = handle_first_arg(cmd, &exit_code);
		if (!should_exit && cmd->args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			data->err = 1;
			return (data->err);
		}
	}
	data->err = exit_code;
	close_inherited_fds(cmd);
	exit_error(data);
	return (-42);
}
