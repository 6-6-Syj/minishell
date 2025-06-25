/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-25 20:36:34 by jmagand           #+#    #+#             */
/*   Updated: 2025-06-25 20:36:34 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_signal.h"
#include <signal.h>
#include <readline/readline.h>

volatile sig_atomic_t	g_sig = 0;

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("ET DE 1\n");
		g_sig = SIGINT;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		ft_printf("ET DE 2\n");
		g_sig = SIGQUIT;
	}
}

bool	init_sig_handler(void)
{
	struct sigaction	sa;

	rl_catch_signals = 1; // readline doesn't handle sig
	sa.quit.sa_handler = SIG_IGN;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0; // for readline todo: check this SA_RESTART
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (false);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (false);
	return (true);
}
