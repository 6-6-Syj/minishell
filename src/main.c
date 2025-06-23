/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c              								:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:59:19 by dabuchhe          #+#    #+#             */
/*   Updated: 2025/04/30 23:04:31 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

// MAYBE USE ISATTY TOO

// input = readline(get_path_term(&data));

// static char *get_path_term(t_data *data)
// {
// 	char	cwd[PATH_MAX];
// 	char	*name;
// 	char	*tmp;
// 	char	*input;

// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	{
// 		tmp = ft_strjoin(cwd, " ");
// 		if (!tmp)
// 			return ("minishell$ ");
// 		name = tmp;
// 		tmp = ft_strjoin(name, get_env_var(data, "USER"));
// 		if (!tmp)
// 			return ("minishell$ ");
// 		name = tmp;
// 		tmp = ft_strjoin(name, "> ");
// 		if (!tmp)
// 			return ("minishell$ ");
// 		name = tmp;
// 		input = name;
// 		name = NULL;
// 		tmp = NULL;
// 	}
// 	else
// 		input = "minishell$ ";
// 	return (input);
// }

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*input;

	(void)ac;
	(void)av;
	init_data(&data, env);
	while (1)
	{
		input = readline("> ");
		if (input[0] != '\0')
			add_history(input);
		if (!input)
			break ;
		data.err = 0;
		init_token(&data.token, input);
		parse_token_lst(&data.token);
		init_ast(&data.ast, &data.token);
		exec_ast(data.ast, &data);
		print_all(&data);
		free(input);
		free_token_lst(&data.token);
		// free_ast(&data.ast);
		data.token = NULL;
	}
	rl_clear_history();
	exit_error(&data);
	return (0);
}
