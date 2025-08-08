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
#include "print.h"

char	*clean_ctrl_char(char *line, t_data *data)
{
    size_t  i;
	size_t	j;
    char    *clean;

	i = 0;
	j = 0;
    if (!line)
        return (NULL);
    clean = malloc(ft_strlen(line) + 1);
    if (!clean)
        malloc_fail(data);
    while (line[i])
    {
        if (line[i] >= ' ' || line[i] == '\n' || line[i] == '\t')
            clean[j++] = line[i];
        i++;
    }
    clean[j] = '\0';
    return (clean);
}

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
