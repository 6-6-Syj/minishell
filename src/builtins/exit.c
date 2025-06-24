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

static bool	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool	handle_first_arg(t_command *cmd, int *exit_code)
{
	long long	num;

	num = 0;
	if (is_valid_number(cmd->args[1]))
	{
		num = ft_atoll_shell(cmd->args[1]);
		*exit_code = (int)(num % 256);
		if (*exit_code < 0)
			*exit_code += 256;
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (false);
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		*exit_code = 2;
		return (true);
	}
}

void	ft_exit(t_command *cmd, t_data *data)
{
	int		exit_code;
	bool	should_exit;

	exit_code = 0;
	should_exit = false;
	if (!cmd->args[1])
	{
		ft_printf("err = %d\n", data->exit_err);
		exit_code = data->exit_err;
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	}
	else
	{
		should_exit = handle_first_arg(cmd, &exit_code);
		if (!should_exit && cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			data->err = 1;
			return ;
		}
	}
	data->err = exit_code;
	close_inherited_fds(cmd);
	exit_error(data);
}
