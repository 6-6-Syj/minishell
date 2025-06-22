/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 18:42:44 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-27 18:42:44 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "redir.h"

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

/*
TODO:
	Search and launch the right executable (based on the PATH variable
	or using a relative or an absolute path).
*/

static void	search_cmd_and_exec(t_command *cmd, t_data *data)
{
	char	*path;

	path = get_path(cmd->args[0], data);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		data->err = 127;
		exit_error(data);
	}
	w_execve(path, cmd->args, data->env_tab, data);
}

void	exec_command(t_command *cmd, t_data *data)
{
	pid_t	pid;

	pid = w_fork(data);
	if (pid == 0)
	{
		open_files(cmd, data);
		close_inherited_fds(cmd);
		if (cmd && cmd->args && cmd->args[0])
		{
			if (is_builtin(cmd->args[0]))
			{
				data->err = exec_builtin(cmd, &data->env, data);
				exit_error(data);
			}
			else
				search_cmd_and_exec(cmd, data);
		}
		exit(1); // TODO: CHECK ERROR
	}
	else
	{
		if (cmd->fd_in > 2)
			w_close(cmd->fd_in, data);
		if (cmd->fd_out > 2)
			w_close(cmd->fd_out, data);
	}
}
