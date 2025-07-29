/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:42:44 by jmagand           #+#    #+#             */
/*   Updated: 2025/06/30 19:08:07 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "print.h"
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

t_pid_list	*get_last_pid(t_pid_list *pid_lst)
{
	t_pid_list	*last;

	last = pid_lst;
	if (!pid_lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	add_pid(t_pid_list **pids, pid_t pid, bool is_last, t_data *data)
{
	t_pid_list	*new_node;
	t_pid_list	*last_node;

	(void)data;
	new_node = ft_calloc(1, sizeof(t_pid_list));
	if (!new_node)
		malloc_fail(data);
	if (!(*pids))
	{
		*pids = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last_node = get_last_pid(*pids);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	new_node->next = NULL;
	new_node->pid = pid;
	new_node->is_last_cmd = is_last;
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
		data->pid_list = NULL;
		if (pids && *pids)
		{
			free_pid_list(pids);
			*pids = NULL;
		}
		open_files(cmd, data);
		close_inherited_fds(cmd);
		exec_command(cmd, data);
	}
	else
	{
		is_last = is_last_command_in_ast(cmd, root);
		add_pid(pids, pid, is_last, data);
		data->pid_list = *pids;
		if (cmd->fd_in > 2)
			w_close(cmd->fd_in, data);
		if (cmd->fd_out > 2)
			w_close(cmd->fd_out, data);
	}
}
