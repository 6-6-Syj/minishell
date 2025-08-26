/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:36:34 by jmagand           #+#    #+#             */
/*   Updated: 2025/07/26 20:52:59 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "handle_signal.h"
#include "libft.h"
#include <readline/readline.h>
#include <signal.h>

extern volatile int	g_sig;

int event_hook(void)
{
    if (g_sig == 1)
    {
        rl_done = 1;
    }
    return (0);
}

void sig_handler_heredoc(int signum)
{
    if (signum == SIGINT)
    {
        g_sig = 1;
    }
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

bool	init_sig_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (false);
	signal(SIGQUIT, SIG_IGN);
	return (true);
}
