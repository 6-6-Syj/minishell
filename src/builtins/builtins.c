/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:16:39 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/08 17:25:10 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	exec_builtin(t_command *cmd, t_env **env_lst, t_data *data)
{
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (ft_pwd(data));
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		return (ft_env(*env_lst));
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(cmd, data));
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		return (handle_export(cmd, env_lst, data));
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (handle_unset(cmd, env_lst, data));
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (ft_exit(cmd, data));
	return (0);
}
