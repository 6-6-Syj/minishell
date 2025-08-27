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

char	*handle_readline(t_data *data)
{
	char	*input;

	g_sig = 0;
	signal(SIGINT, sig_handler);
	input = readline("minishell$ ");
	signal(SIGINT, SIG_IGN);
	if (g_sig)
	{
		data->err = 130;
		g_sig = 0;
	}
	if (!input)
		clean_exit(data);
	if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	add_history(input);
	return (input);
}

static void	check_tty(int ac, char **av, t_data *data)
{
	(void)ac;
	(void)av;
	if (!isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("minishell: stdout is not a tty\n", STDERR_FILENO);
		data->err = 130;
		exit_error(data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	check_tty(ac, av, &data);
	init_data(&data, env);
	while (1)
	{
		data.is_nl = false;
		data.input = handle_readline(&data);
		if (!data.input)
			continue ;
		init_token(&data);
		if (data.syntax == 0)
		{
			// print_all(&data);
			init_ast(&data.ast, &data.token, &data);
			data.err = 0;
		}
		else
			data.err = 2;
		if (g_sig == 0 && !data.err)
			exec_ast(data.ast, &data);
		if (g_sig)
			data.err = 130;
		free_tmp_data(&data);
		data.token = NULL;
	}
	rl_clear_history();
	return (0);
}
