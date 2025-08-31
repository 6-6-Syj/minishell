/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:42:44 by jmagand           #+#    #+#             */
/*   Updated: 2025/08/26 16:25:00 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "redir.h"
#include "wrappers.h"
#include "exec.h"
#include "builtins.h"

static void	check_access(char *path, t_command *cmd, t_data *data)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		data->err = 127;
		free(path);
		exit_error(data);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		free(path);
		data->err = 126;
		exit_error(data);
	}
}

static void	exec_in_current_dir(t_command *cmd, t_data *data)
{
	char	*cwd_path;

	cwd_path = ft_strjoin("./", cmd->args[0]);
	if (!cwd_path)
		malloc_fail(data);
	if (access(cwd_path, F_OK) == 0)
	{
		check_access(cwd_path, cmd, data);
		w_execve(cwd_path, cmd->args, data->env_tab, data);
	}
	free(cwd_path);
	no_file_or_directory(cmd, data);
}

static void	search_cmd_and_exec(t_command *cmd, t_data *data)
{
	char			*path;
	t_path_status	status;

	path = resolve_command_path(cmd->args[0], data, &status);
	if (status == PATH_UNSET)
	{
		if (is_absolute_or_relative_path(cmd->args[0]))
		{
			path = ft_strdup(cmd->args[0]);
			if (!path)
				malloc_fail(data);
			check_access(path, cmd, data);
			w_execve(path, cmd->args, data->env_tab, data);
		}
		else
			exec_in_current_dir(cmd, data);
		return ;
	}
	if (status == PATH_NOT_FOUND)
		cmd_not_found(cmd, data);
	check_access(path, cmd, data);
	w_execve(path, cmd->args, data->env_tab, data);
}

static void	exec_command(t_command *cmd, t_data *data)
{
	if (cmd && cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
		{
			if (!data->err)
				data->err = exec_builtin(cmd, &data->env, data);
			exit_error(data);
		}
		else if (is_a_dir(cmd, data))
			exit_error(data);
		else
		{
			if (!data->err)
				search_cmd_and_exec(cmd, data);
			else
				data->err = 1;
		}
	}
	exit_error(data); //TODO: CHECK ERROR CODE THERE
}

void	handle_command(t_command *cmd, t_data *data)
{
	pid_t	pid;

	pid = w_fork(data);
	if (pid == 0)
	{
		open_files(cmd, data);
		close_inherited_fds(cmd);
		if (!ft_strcmp(cmd->args[0], "(null)") && cmd->fd_out != -1)
			w_close(cmd->fd_out, data);
		if (!ft_strcmp(cmd->args[0], "(null)") && cmd->fd_in != -1)
			w_close(cmd->fd_in, data);
		if (!data->err)
			exec_command(cmd, data);
		else
			exit_error(data);
	}
	else
	{
		if (cmd->is_last_cmd)
			data->last_cmd_pid = pid;
		if (cmd->fd_in > 2)
			w_close(cmd->fd_in, data);
		if (cmd->fd_out > 2)
			w_close(cmd->fd_out, data);
	}
}
