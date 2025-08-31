/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:01:46 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/08 18:34:52 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "wrappers.h"

void	close_inherited_fds(t_command *cmd)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		if (fd != cmd->fd_in && fd != cmd->fd_out)
			close(fd);
		fd++;
	}
}

void	redir(t_command *cmd, t_data *data)
{
	if (cmd && cmd->fd_in > 0 && cmd->fd_in != STDIN_FILENO)
	{
		w_dup2(cmd->fd_in, STDIN_FILENO, data);
		w_close(cmd->fd_in, data);
	}
	if (cmd && cmd->fd_out > 1 && cmd->fd_out != STDOUT_FILENO)
	{
		w_dup2(cmd->fd_out, STDOUT_FILENO, data);
		w_close(cmd->fd_out, data);
	}
}

void	redir_builtin_solo(int *fd_in, int *fd_out, t_data *data)
{
	if (*fd_in > 0 && *fd_in != STDIN_FILENO)
	{
		w_dup2(*fd_in, STDIN_FILENO, data);
		w_close(*fd_in, data);
	}
	if (*fd_out > 1 && *fd_out != STDOUT_FILENO)
	{
		w_dup2(*fd_out, STDOUT_FILENO, data);
		w_close(*fd_out, data);
	}
}

static bool	is_special_input(t_command *cmd, t_data *data)
{
	if (!ft_strcmp(".", cmd->args[0]))
	{
		ft_putstr_fd("minishell: .: filename argument required\n",
			STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		data->err = 2;
		return (true);
	}
	if (!ft_strcmp("..", cmd->args[0]))
	{
		ft_putstr_fd("minishell: ..: command not found\n", STDERR_FILENO);
		data->err = 127;
		return (true);
	}
	return (false);
}

bool	is_a_dir(t_command *cmd, t_data *data)
{
	struct stat	info;

	if (is_special_input(cmd, data))
		return (true);
	if (stat(cmd->args[0], &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			data->err = 126;
			return (true);
		}
		return (false);
	}
	else
		return (false);
}
