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

static void	close_inherited_fds(t_command *cmd)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		// Ne pas fermer les FDs que nous utilisons
		if (fd != cmd->fd_in && fd != cmd->fd_out)
			close(fd);
		fd++;
	}
}

static void	search_cmd_and_exec(t_command *cmd, t_data *data)
{
	char	*path;

	path = get_path(cmd->args[0], data);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->args[0]);
		exit_error(data); // TODO: 127 ?
	}
	w_execve(path, cmd->args, data->env_tab, data);
}

void	exec_command(t_command *cmd, t_data *data)
{
	pid_t	pid;

	pid = w_fork(data);
	if (pid == 0) // CHILD PROCESS
	{
		redir_in(cmd, data);
		redir_out(cmd, data);
		close_inherited_fds(cmd);
		if (cmd && cmd->args && cmd->args[0])
		{
			if (is_builtin(cmd->args[0])) // TODO: CHECK THIS IN MULTI-PIPE
			{
				data->err = exec_builtin(&data->env, data, cmd->args[0]);
				exit(0); // TODO: CHECK ERROR
			}
			else
				search_cmd_and_exec(cmd, data);
		}
		exit(1); // TODO: CHECK ERROR
	}
	else // PARENT PROCESS
	{
		if (cmd->fd_in > 2)
			w_close(cmd->fd_in, data);
		if (cmd->fd_out > 2)
			w_close(cmd->fd_out, data);
	}
}
