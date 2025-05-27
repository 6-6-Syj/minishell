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

#include "builtins.h"

// static void	free_env_list(t_env *head)
// {
// 	t_env	*tmp;

// 	while (head)
// 	{
// 		tmp = head;
// 		head = head->next;
// 		if (tmp->key)
// 			free(tmp->key);
// 		if (tmp->value)
// 			free(tmp->value);
// 		free(tmp);
// 	}
// }

// static void	print_env_list(t_env *head)
// {
// 	while (head)
// 	{
// 		ft_printf("%s=%s\n", head->key, head->value);
// 		head = head->next;
// 	}
// 	ft_printf("\n");
// }

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	exec_builtin(t_env **env_lst, t_data *data, char *input)
{
	if (!ft_strncmp(input, "env", 4)) // ft_strtrim(input, "\"")
		return (ft_env(*env_lst));
	else if (!ft_strncmp(input, "pwd", 4))
		return (ft_pwd());
	// else if (!ft_strncmp(input, "echo", 5)) // care -n
	// 	ft_echo(env);
	else if (!ft_strncmp(input, "cd", 3))
		return (handle_cd(*env_lst, input));
	else if (!ft_strncmp(input, "export", 7))
		return (handle_export(env_lst, data, input));
	else if (!ft_strncmp(input, "unset", 6))
		return (handle_unset(env_lst, data, input));
	// else if (!ft_strncmp(input, "exit", 5))
	// 	ft_exit(env);
	return (0);
}
