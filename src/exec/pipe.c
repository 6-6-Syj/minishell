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
	if (!node)
		return ;
	if (node->type == COMMAND)
	{
		if (fd_in != -1)
			node->command.fd_in = fd_in;
		if (fd_out != -1)
			node->command.fd_out = fd_out;
	}
	else if (node->type == PIPE)
	{
		assign_pipe_fds(node->pipe.left, fd_in, -1); // left inherits fd_in
		assign_pipe_fds(node->pipe.right, -1, fd_out); // right inherits fd_out
	}
}

void	handle_pipe(t_pipe *pipe, t_data *data, int *fd)
{
	w_pipe(fd, data);
	if (pipe->left->type == COMMAND)
		pipe->left->command.fd_out = fd[1];
	else if (pipe->left->type == PIPE)
		assign_pipe_fds(pipe->left, -1, fd[1]);
	if (pipe->right->type == COMMAND)
		pipe->right->command.fd_in = fd[0];
	else if (pipe->right->type == PIPE)
		assign_pipe_fds(pipe->right, fd[0], -1);
	handle_ast(pipe->left, data, fd);
	// No check, normal: if w_close: crash. ex sur bash (sleep 2 | cat -e)
	close(fd[1]);
	handle_ast(pipe->right, data, fd);
	// No check, normal: if w_close: crash. ex sur bash (sleep 2 | cat -e)
	close(fd[0]);
}
