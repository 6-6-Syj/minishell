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


// Allouer data sur la heap au lieu de la stack !
//
int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*input;
	int		fd[2];

	(void)ac;
	(void)av;
	init_data(&data);
	init_env(&data, env);
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	while (1)
	{
		input = readline("> ");
		if (input[0] != '\0')
			add_history(input);
		if (!input)
			break ;
		init_token(&data.token, input);
		init_ast_lst(&data.ast); // test version
		handle_ast(data.ast, &data, fd);
		ft_buitins(&data.env, &data, input);
		print_all(&data);
		free(input);
		free_token_lst(&data.token);
		data.token = NULL;
	}
	rl_clear_history();
	// exit_error(&data);
	return (0);
}
