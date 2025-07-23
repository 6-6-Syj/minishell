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
#include "libft.h"
#include <readline/readline.h>
#include <signal.h>

extern volatile int	g_sig;

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
        // rl_done = 1;
	}
}

bool	init_sig_handler(void)
{
	struct sigaction	sa;

	rl_catch_signals = 1;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (false);
	// Pour SIGQUIT, ignorer quand pas dans un processus fils
	signal(SIGQUIT, SIG_IGN);
	return (true);
}
