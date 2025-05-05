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

// // static void	print_env_list(t_env *head)
// // {
// // 	while (head)
// // 	{
// // 		printf("%s=%s\n", head->key, head->value);
// // 		head = head->next;
// // 	}
// // }

// static t_env	*env_to_list(char **env)
// {
// 	t_env	*head;
// 	t_env	*new_node;
// 	char	*equal;
// 	char	*key;
// 	char	*value;
// 	int		i;

// 	head = NULL;
// 	i = -1;
// 	while (env[++i])
// 	{
// 		equal = ft_strchr(env[i], '=');
// 		if (equal)
// 		{
// 			key = ft_strndup(env[i], equal - env[i]);
// 			value = ft_strdup(equal + 1);
// 			new_node = malloc(sizeof(t_env));
// 			if (!new_node || !key || !value)
// 			{
// 				free(key);
// 				free(value);
// 				// TODO: FREE NODES ALREADY CREATED
// 				return (NULL);
// 			}
// 			new_node->key = key;
// 			new_node->value = value;
// 			new_node->next = head;
// 			head = new_node;
// 		}
// 	}
// 	return (head);
// }

// static int	ft_buitins(char **env)
// {
// 	char	*read;
// 	t_env	*env_lst;
// 	char	**args;
// 	int		j;

// 	env_lst = env_to_list(env);
// 	if (!env_lst)
// 	{
// 		printf("Error malloc env_lst\n");
// 		return (1);
// 	}
// 	while ("Minishell is running")
// 	{
// 		read = readline("\033[0;31m\033[1m66Syj_\033[0m ");
// 		if (!read)
// 			return (1); // (NULL)
// 		add_history(read);
// 		if (!ft_strcmp(read, "env")) // ft_strtrim(read, "\"")
// 			ft_env(env_lst);
// 		else if (!ft_strcmp(read, "pwd"))
// 			ft_pwd();
// 		// else if (!ft_strcmp(read, "echo")) // care -n
// 		// 	ft_echo(env);
// 		// else if (!ft_strcmp(read, "cd"))
// 		// 	ft_cd(env);
// 		else if (!ft_strcmp(read, "export"))
// 			ft_export(env_lst);
// 		else if (!ft_strncmp(read, "unset", 5))
// 		{
// 			args = ft_split(read, ' ');
// 			if (args && args[1])
// 				ft_unset(&env_lst, args[1]);
// 			j = 0;
// 			while (args && args[j])
// 				free(args[j++]);
// 			free(args);
// 		}
// 		// else if (!ft_strcmp(read, "exit"))
// 		// 	ft_exit(env);
// 	}
// 	free_env_list(env_lst);
// 	rl_clear_history();
// 	return (0);
// }
