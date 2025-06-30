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
#include <stdio.h>

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

static void	cmd_not_found(t_command *cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	data->err = 127;
	exit_error(data);
}

static void	search_cmd_and_exec(t_command *cmd, t_data *data)
{
	char	*path;
	bool	is_path_unset;
	char	**tmp_paths;

	path = get_path(cmd->args[0], data);
	is_path_unset = true;
	if (!path && !is_absolute_or_relative_path(cmd->args[0]))
	{
		tmp_paths = split_path(data);
		if (tmp_paths)
		{
			is_path_unset = false;
			free_strs(tmp_paths);
		}
	}
	else if (path || is_absolute_or_relative_path(cmd->args[0]))
		is_path_unset = false;
	if (!path && !is_path_unset)
		cmd_not_found(cmd, data);
	else if (!path)
		exit_error(data);
	check_access(path, cmd, data);
	w_execve(path, cmd->args, data->env_tab, data);
}

// static void	search_cmd_and_exec(t_command *cmd, t_data *data)
// {
// 	char	*path;
// 	bool	is_path_unset;

// 	is_path_unset = true;
// 	if (split_path(data))
// 		is_path_unset = false;
// 	path = get_path(cmd->args[0], data);
// 	if (!path && !is_path_unset)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 		ft_putendl_fd(": command not found", STDERR_FILENO);
// 		data->err = 127;
// 		exit_error(data);
// 	}
// 	else if (!path)
// 		exit_error(data);
// 	check_access(path, cmd, data);
// 	w_execve(path, cmd->args, data->env_tab, data);
// }

static void	add_pid(t_pid_list **pids, pid_t pid, bool is_last, t_data *data)
{
	t_pid_list	*new_pid;

	new_pid = malloc(sizeof(t_pid_list));
	if (!new_pid)
		exit_error(data);
	new_pid->pid = pid;
	new_pid->is_last_cmd = is_last;
	new_pid->next = *pids;
	*pids = new_pid;
}

#include <sys/stat.h>
#include <sys/types.h>

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

static bool	is_a_dir(t_command *cmd, t_data *data)
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
	exit(1); // TODO: CHECK THIS
}

void	handle_command(t_command *cmd, t_data *data, t_pid_list **pids,
		t_ast *root)
{
	pid_t	pid;
	bool	is_last;

	pid = w_fork(data);
	if (pid == 0)
	{
		open_files(cmd, data);
		close_inherited_fds(cmd);
		exec_command(cmd, data);
	}
	else
	{
		is_last = is_last_command_in_ast(cmd, root);
		add_pid(pids, pid, is_last, data);
		if (cmd->fd_in > 2)
			w_close(cmd->fd_in, data);
		if (cmd->fd_out > 2)
			w_close(cmd->fd_out, data);
	}
}
