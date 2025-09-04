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

static bool	handle_first_arg(t_command *cmd, int *exit_code, t_data *data)
{
	long long	num;

	num = ft_atoll_shell(cmd->args[1], data);
	if (!data->err)
	{
		*exit_code = (int)(num % 256);
		if (*exit_code < 0)
			*exit_code += 256;
		if (!data->exit_pipe)
			ft_putendl_fd("exit", STDERR_FILENO);
		return (false);
	}
	else
	{
		if (!data->exit_pipe)
			ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
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
		if (!data->exit_pipe)
			ft_putendl_fd("exit", STDERR_FILENO);
	}
	else
	{
		should_exit = handle_first_arg(cmd, &exit_code, data);
		if (!should_exit && cmd->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments",
				STDERR_FILENO);
			data->err = 1;
			return (data->err);
		}
	}
	data->err = exit_code;
	exit_error(data);
	return (-42);
}
