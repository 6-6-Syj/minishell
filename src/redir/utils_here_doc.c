/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 22:58:03 by jmagand           #+#    #+#             */
/*   Updated: 2025-07-25 22:58:03 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

int	disable_ctrl_backslash(struct termios *saved_termios)
{
	struct termios	new_termios;

	if (tcgetattr(STDIN_FILENO, saved_termios) == -1)
	{
		perror("tcgetattr");
		return (-1);
	}
	new_termios = *saved_termios;
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	new_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
	{
		perror("tcsetattr");
		return (-1);
	}
	return (0);
}
