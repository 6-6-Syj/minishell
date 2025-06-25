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

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data);
	init_env(&data, env);
	while (1)
	{
		data.input = readline("> ");
		if (data.input[0] != '\0')
			add_history(data.input);
		if (!data.input)
			break ;
		init_token(&data);
		parse_token_lst(&data.token);
		init_ast(&data.ast, &data.token);
		// exec_ast(data.ast, &data);
		print_all(&data);
		free(data.input);
		free_token_lst(&data.token);
		free_ast(&data.ast);
		data.token = NULL;
	}
	rl_clear_history();
	exit_error(&data);
	return (0);
}
