/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-20 16:15:44 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-20 16:15:44 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include <readline/readline.h>

extern volatile int	g_sig;

bool ctrl_c_catched(char *line, int fd, char *filename)
{
    if (g_sig == 1)
    {
        if (line)
            free(line);
        close(fd);
        unlink(filename);
        signal(SIGINT, SIG_IGN);
        rl_event_hook = NULL;
        return (true);
    }
    return (false);
}

bool eof_catched(char *line, int fd, t_redir *redir, t_data *data)
{
    if (!line || !ft_strcmp(handle_expand(line, 0, data), redir->delimiter))
    {
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
            ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
            ft_putstr_fd(redir->delimiter, STDERR_FILENO);
            ft_putstr_fd("')\n", STDERR_FILENO);
        }
        close(fd);
        signal(SIGINT, SIG_IGN);
        rl_event_hook = NULL;
        return (true);
    }
    return (false);
}
