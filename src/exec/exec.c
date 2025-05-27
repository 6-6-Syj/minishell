/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 18:36:22 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-09 18:36:22 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "data.h"
#include "env.h"
#include "exec.h"
#include "command.h"

static void	handle_ast(t_ast *node, t_data *data, int *fd);

static void	handle_exec(t_command *command, t_data *data)
{
	if (is_builtin(command->args[0])) // NOT OK
		exec_builtin(&data->env, data, command->args[0]);
	else
		exec_command(command, data);
}

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
		assign_pipe_fds(node->pipe.left, fd_in, -1);   // left inherits fd_in
		assign_pipe_fds(node->pipe.right, -1, fd_out); // right inherits fd_out
	}
}

static void	handle_pipe(t_pipe *pipe, t_data *data, int *fd)
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

// static int	handle_and_or(t_ast *node, t_data *data)
// {
// 	ret = handle_ast(node->logic.left, data);
// 	if (node->type == AND)
// 	{
// 		if (ret == 0)
// 			ret = handle_ast(node->logic.right, data);
// 	}
// 	else // type == OR
// 	{
// 		if (ret != 0)
// 			ret = handle_ast(node->logic.right, data);
// 	}
// 	return (ret);
// }

static void	handle_ast(t_ast *node, t_data *data, int *fd)
{
	if (!node)
		return ;
	// else if (node && (node->type == AND || node->type == OR))
	// 	handle_and_or(node, data);
	if (node && (node->type == REDIR_IN_TRUNC || node->type == REDIR_OUT_TRUNC
			|| node->type == REDIR_OUT_APPEND || node->type == HERE_DOC))
	{
		// Handle redirect stdin/out
		// Ouvrir le fichier approprié en fonction du type de redirection
		// Dupliquer les descripteurs de fichiers standards
		// Fermer les descripteurs de fichiers inutiles
		// Si un sous-arbre droit existe,
		// cela signifie qu'il y a d'autres redirections à faire
		// Si tout se passe bien à droite,
		// continuer à gauche ou exécuter la commande
		// Si problème à droite, retourner le code d'erreur du sous-arbre droit
		// return (-42);
	}
	else if (node->type == COMMAND)
		handle_exec(&node->command, data);
	else if (node->type == PIPE)
		handle_pipe(&node->pipe, data, fd);
}

static void	wait_process(void)
{
	int		status;
	pid_t	wpid;

	while ((wpid = wait(&status)) > 0)
	{
		ft_printf("\033[0;32m\033[1m");
		ft_printf("Child PID %d ended with status %d\n", wpid, status);
		ft_printf("\033[0m");
	}
}
void	exec_ast(t_ast *node, t_data *data)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	handle_ast(node, data, fd);
	wait_process();
}

/*	TESTS

ls | cat -e | sleep 2 | ls | cat -e | cat -e

sleep 1 | sleep 2 | sleep 6 | ls | sleep 6 | cat -e | sleep 2 | ls | cat
	-e | sleep 1 | sleep 2 | sleep 6 | ls | sleep 6 | cat
	-e | sleep 2 | ls | cat
	-e | sleep 1 | sleep 2 | sleep 6 | ls | sleep 6 | cat
	-e | sleep 2 | ls | cat -e

*/
