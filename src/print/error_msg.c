/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-05 19:37:11 by jmagand           #+#    #+#             */
/*   Updated: 2025-07-05 19:37:11 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

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
