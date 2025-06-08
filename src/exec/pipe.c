/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 19:12:25 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-27 19:12:25 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	assign_pipe_fds(t_ast *node, int fd_in, int fd_out)
{
	// ft_printf("\nASSIGN\n");
	if (!node)
		return ;
	if (node->type == COMMAND)
	{
        // ft_printf("COMMAND %s\n", node->command.args[0]);
		if (fd_in != -1)
		{
            // ft_printf("-> Assignation de fd_in = %d\n", fd_in);
			node->command.fd_in = fd_in;
		}
		if (fd_out != -1)
		{
            // ft_printf("-> Assignation de fd_out = %d\n", fd_out);
			node->command.fd_out = fd_out;
		}
	}
	else if (node->type == PIPE)
	{
		// ft_printf("PIPE\n");
        // ft_printf("-> Appel récursif à gauche avec fd_in = %d, fd_out = -1\n", fd_in);
		assign_pipe_fds(node->pipe.left, fd_in, -1); // left inherits fd_in
        // ft_printf("-> Appel récursif à droite avec fd_in = -1, fd_out = %d\n", fd_out);
		assign_pipe_fds(node->pipe.right, -1, fd_out); // right inherits fd_out
	}
}

void	handle_pipe(t_pipe *pipe, t_data *data, int *fd)
{
	w_pipe(fd, data);
    // ft_printf("\n\tHANDLE\nPipe crated: fd[0] = %d (in), fd[1] = %d (out)\n", fd[0], fd[1]);
	if (pipe->left->type == COMMAND)
	{
        // ft_printf("-> Assign à gauche du pipe (COMMAND) : fd_out = %d\n", fd[1]);
		pipe->left->command.fd_out = fd[1];
	}
	else if (pipe->left->type == PIPE)
	{
		// ft_printf("-> Assign récursive à gauche (PIPE) : fd_out = %d\n", fd[1]);
		assign_pipe_fds(pipe->left, -1, fd[1]);
	}
	if (pipe->right->type == COMMAND)
	{
		// ft_printf("-> Assign à droite du pipe (COMMAND) : fd_in = %d\n", fd[0]);
		pipe->right->command.fd_in = fd[0];
	}
	handle_ast(pipe->left, data, fd);
	// No check, normal: if w_close: crash. ex sur bash (sleep 2 | cat -e)
	handle_ast(pipe->right, data, fd);
	// No check, normal: if w_close: crash. ex sur bash (sleep 2 | cat -e)
	close(fd[1]);
	close(fd[0]);
}
