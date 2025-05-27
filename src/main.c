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
	char	*input;

	(void)ac;
	(void)av;
	init_data(&data);
	init_env(&data, env);
	while (1)
	{
		input = readline("> ");
		if (input[0] != '\0')
			add_history(input);
		if (!input)
			break ;
		init_token(&data.token, input);
		init_ast(&data.ast, &data.token);
		// print_all(&data);
		exec_ast(data.ast, &data);
		free(input);
		free_token_lst(&data.token);
		free_ast(&data.ast);
		data.token = NULL;
	}
	rl_clear_history();
	// exit_error(&data);
	return (0);
}
