/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:40 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/18 23:47:13 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "command.h"
#include <unistd.h>
#include "libft.h"

void	exit_error(t_data *data)
{
	int	err;

	err = 0;
	if (data)
	{
		if (data->err_msg)
		{
			ft_putstr_fd(data->err_msg, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		err = data->err;
		free_data(data);
	}
	exit(err);
}

void	cmd_not_found(t_command *cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	data->err = 127;
	exit_error(data);
}

void	no_file_or_directory(t_command *cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	data->err = 127;
	exit_error(data);
}

void	malloc_fail(t_data *data)
{
	data->err = 1;
	data->err_msg = "minishell: Malloc failed";
	exit_error(data);
}

void	syntax_error(t_data *data)
{
	data->err = 2;
	data->err_msg = "minishell: Syntax error";
	exit_error(data);
}
