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
#include <signal.h>

volatile int	g_sig;

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

// static char	*handle_readline(t_data *data)
// {
// 	char	*line;
// 	char	*str;
// 	int		fd;

// 	fd = 3;
// 	if (isatty(fileno(stdin)))
// 	{
// 		str = readline(">");
// 		if (!str)
// 		{
// 			ft_printf("exit\n");
// 			while (fd < 1024)
// 				close(fd++);
// 			exit_error(data);
// 			return (NULL);
// 		}
// 		if (str[0] != '\0')
// 			add_history(str);
// 		else
// 		{
// 			free(str);
// 			return (NULL);
// 		}
// 	}
// 	else
// 	{
// 		str = get_next_line(fileno(stdin));
// 		if (str)
// 		{
// 			line = ft_strtrim(str, "\n");
// 			free(str);
// 			str = line;
// 		}
// 		if (!str)
// 		{
// 			ft_printf("exit\n");
// 			while (fd < 1024)
// 				close(fd++);
// 			exit_error(data);
// 			return (NULL);
// 		}
// 	}
// 	return (str);
// }

volatile sig_atomic_t	g_sig;

static char	*handle_readline(t_data *data)
{
	char	*line;
	int		fd;

	char	*str;
	fd = 3;

	if (isatty(fileno(stdin)))
		str = readline(">");
	else
	{
		str = get_next_line(fileno(stdin));
		if (str)
		{
			line = ft_strtrim(str, "\n");
			free(str);
			str = line;
		}
		if (!str)
		{
			// ft_printf("exit\n");
			// while (fd < 1024)
			// 	close(fd++);
			exit_error(data);
			return (NULL);
		}
	}
	// line = readline("> ");
	// if (str[0] != '\0')
	// 	add_history(str);
	// else
	// {
	// 	free(str);
	// 	return (NULL);
	// }
	// return (str);
	return (str);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	while (1)
	{
		data.input = handle_readline(&data);
		if (!data.input)
			continue ;
		data.err = 0;
		if (g_sig == SIGINT)
		{
			// ft_printf("CATCHED\n");
			g_sig = 0;
		}
		init_token(&data);
		// print_all(&data);
		init_ast(&data.ast, &data.token, &data);
		exec_ast(data.ast, &data);
		free_tmp_data(&data);
		data.token = NULL;
	}
	rl_clear_history();
	return (0);
}
