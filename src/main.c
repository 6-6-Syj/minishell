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

#include "ast.h"
#include "data.h"
#include "env.h"
#include "exec.h"
#include "wrappers.h"
#include "handle_signal.h"
#include "libft.h"
#include "token.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

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
	ft_putstr_fd("exit\n", STDERR_FILENO);
	rl_clear_history();
	exit(data->err);
}

char	*handle_readline(t_data *data)
{
	char	*input;

	g_sig = 0;
	w_signal(SIGINT, sig_handler, data);
	input = readline("minishell$ ");
	w_signal(SIGINT, SIG_IGN, data);
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
	int	fd;

	fd = 3;
	(void)ac;
	(void)av;
	if (!isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("minishell: stdout is not a tty\n", STDERR_FILENO);
		while (fd < 1024)
		{
			close(fd);
			fd++;
		}
		data->err = 130;
		exit(data->err);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	check_tty(ac, av, &data);
	init_data(&data, env);
	while (1)
	{
		data.input = handle_readline(&data);
		if (!data.input)
			continue ;
		init_token(&data);
		if (data.syntax_err == false)
			init_ast(&data.ast, &data.token, &data);
		else
			data.err = 2;
		if (data.err)
			data.exit_err = data.err;
		if (g_sig == 0 && !data.err)
			exec_ast(data.ast, &data);
		free_tmp_data(&data);
		data.exit_pipe = false;
	}
	rl_clear_history();
	return (0);
}
