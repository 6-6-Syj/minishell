/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:16:39 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/05/05 20:16:50 by dabuchhe         ###   ########lyon.fr   */
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

int	ft_buitins(t_env **env_lst, char *input)
{
	if (!ft_strncmp(input, "env", 3)) // ft_strtrim(input, "\"")
		return (ft_env(*env_lst));
	else if (!ft_strncmp(input, "pwd", 3))
		return (ft_pwd());
	// else if (!ft_strncmp(input, "echo", 4)) // care -n
	// 	ft_echo(env);
	// else if (!ft_strncmp(input, "cd", 2))
	// 	ft_cd(env);
	else if (!ft_strncmp(input, "export", 6))
		return (handle_export(env_lst, input));
	else if (!ft_strncmp(input, "unset", 5))
		return (handle_unset(env_lst, input));
	// else if (!ft_strncmp(input, "exit", 4))
	// 	ft_exit(env);
	return (0);
}
