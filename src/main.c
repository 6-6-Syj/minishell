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

#include "handle_signal.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

volatile int	g_sig;

static void	clean_exit(t_data *data)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	if (data->env)
		free_env_lst(&data->env);
	if (data->env_tab)
		free_env_tab(data);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	rl_clear_history();
	exit(data->err);
}

static char	*handle_readline(t_data *data)
{
	char	*line;
	char	*str;

	if (isatty(fileno(stdin)))
	{
		signal(SIGINT, sig_handler);
		str = readline("minishell$ ");
		signal(SIGINT, SIG_IGN);
		if (!str)
			clean_exit(data);
		if (str[0] == '\0')
		{
			free(str);
			return (NULL);
		}
		add_history(str);
		return (str);
	}
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
			exit_error(data);
			return (NULL);
		}
	}
	return (str);
}

// char	*handle_readline(t_data *data)
// {
// 	char	*input;

// 	g_sig = 0;
// 	signal(SIGINT, sig_handler);
// 	input = readline("minishell$ ");
// 	signal(SIGINT, SIG_IGN);
// 	if (!input)
// 		clean_exit(data);
// 	if (input[0] == '\0')
// 	{
// 		free(input);
// 		return (NULL);
// 	}
// 	add_history(input);
// 	return (input);
// }

// static void	check_tty(int ac, char **av, t_data *data)
// {
// 	(void)ac;
// 	(void)av;
// 	if (!isatty(STDOUT_FILENO))
// 	{
// 		ft_putstr_fd("minishell: stdout is not a tty\n", STDERR_FILENO);
// 		data->err = 130;
// 		exit_error(data);
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	// check_tty(ac, av, &data);
	init_data(&data, env);
	while (1)
	{
		data.is_nl = false;
		g_sig = 0; // TODO: check
		data.input = handle_readline(&data);
		if (!data.input)
			continue ;
		init_token(&data);
		if (data.syntax == 0)
		{
			init_ast(&data.ast, &data.token, &data);
			data.err = 0;
		}
		else
			data.err = 2;
		if (g_sig == 0 && !data.err)
			exec_ast(data.ast, &data);
		free_tmp_data(&data);
		data.token = NULL;
	}
	rl_clear_history();
	return (0);
}
