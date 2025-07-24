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
#include "handle_signal.h"

volatile int			g_sig;

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

volatile sig_atomic_t	g_sig;

// static char	*handle_readline(t_data *data)
// {
// 	char	*line;

// 	(void)data;
// 	line = readline("> ");
// 	if (line[0] != '\0')
// 		add_history(line);
// 	else
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	return (line);
// }

// static char	*handle_readline(t_data *data)
// {
// 	char	*line;
// 	int		fd;
// 	char	*str;

// 	fd = 3;
// 	if (isatty(fileno(stdin)))
// 		str = readline(">");
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
// 			// ft_printf("exit\n");
// 			// while (fd < 1024)
// 			// 	close(fd++);
// 			exit_error(data);
// 			return (NULL);
// 		}
// 	}
// 	// line = readline("> ");
// 	// if (str[0] != '\0')
// 	// 	add_history(str);
// 	// else
// 	// {
// 	// 	free(str);
// 	// 	return (NULL);
// 	// }
// 	// return (str);
// 	return (str);
// }

char	*handle_readline(t_data *data)
{
	char	*input;

	rl_done = 0;
	g_sig = 0;
	signal(SIGINT, sig_handler);
	input = readline("> ");
	signal(SIGINT, SIG_IGN);
	if (!input)
	{
		ft_printf("exit\n");
		exit_error(data);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	add_history(input);
	return (input);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	while (1)
	{
		data.is_nl = false;
		g_sig = 0;
		data.input = handle_readline(&data);
		init_token(&data);
		init_ast(&data.ast, &data.token, &data);
		data.err = 0;
		exec_ast(data.ast, &data);
		free_tmp_data(&data);
		data.token = NULL;
	}
	rl_clear_history();
	return (0);
}
