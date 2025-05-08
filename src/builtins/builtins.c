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

int	ft_buitins(t_env **env_lst, char *input)
{
	if (!ft_strcmp(input, "env")) // ft_strtrim(input, "\"")
		return (ft_env(*env_lst));
	else if (!ft_strcmp(input, "pwd"))
		return (ft_pwd());
	// else if (!ft_strcmp(input, "echo")) // care -n
	// 	ft_echo(env);
	// else if (!ft_strcmp(input, "cd"))
	// 	ft_cd(env);
	else if (!ft_strcmp(input, "export"))
		return (handle_export(env_lst, input));
	else if (!ft_strncmp(input, "unset", 5))
		return (handle_unset(env_lst, input));
	// else if (!ft_strcmp(input, "exit"))
	// 	ft_exit(env);
	return (0);
}
