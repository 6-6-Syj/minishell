/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:36:22 by jmagand           #+#    #+#             */
/*   Updated: 2025/06/20 18:00:22 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "data.h"
#include "env.h"
#include "exec.h"

/*

Création des processus enfants : Pour chaque commande dans l’AST,
	créer un processus enfant via fork() pour l'exécution de la commande.

Gestion des redirections : Avant de lancer l'exécution,
	configurer les redirections de fichiers et les pipes pour
		que les commandes puissent fonctionner comme prévu.

Si une redirection est présente (par exemple, >, <, >>, 2>),
	les descripteurs de fichiers doivent être modifiés
		avant d'exécuter la commande.

Redirection des flux standard (stdin, stdout,
	stderr) selon les opérateurs dans la commande.

*/

static void	handle_ast(t_ast *node, t_data *data, int *fd);
static void	exec_command(t_command *cmd, t_data *data);

static int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

static void	handle_exec(t_command *command, t_data *data)
{
	if (is_builtin(command->args[0])) // if pipeline, need to fork
		exec_builtin(&data->env, data, command->args[0]);
	else
		exec_command(command, data);
}

static void	exec_command(t_command *cmd, t_data *data)
{
	pid_t	pid;
	char	*path;

	path = NULL;
	pid = w_fork(data);
	if (pid == 0) // CHILD PROCESS
	{
		ft_printf("\nexec_cmd \t%s", cmd->args[0]);
		ft_printf("\tin = %d, out = %d\n", cmd->fd_in, cmd->fd_out);
		if (cmd->fd_in > 0 && cmd->fd_in != STDIN_FILENO)
		{
			w_dup2(cmd->fd_in, STDIN_FILENO, data);
			w_close(cmd->fd_in, data);
		}
		if (cmd->fd_out > 1 && cmd->fd_out != STDOUT_FILENO)
		{
			w_dup2(cmd->fd_out, STDOUT_FILENO, data);
			w_close(cmd->fd_out, data);
		}
		if (cmd && cmd->args && cmd->args[0])
		{
			if (is_builtin(cmd->args[0]))
			{
				exec_builtin(&data->env, data, cmd->args[0]);
				exit(0); // TODO: CHECK IF THERE ?
			}
			else
			{
				path = get_path(cmd->args[0], data);
				if (!path)
				{
					ft_printf("minishell: %s: command not found\n",
						cmd->args[0]);
					exit_error(data); // TODO: 127 ?
				}
				// if (cmd->fd_in > 2)
				// 	w_close(cmd->fd_in, data);
				// if (cmd->fd_out > 2)
				// 	w_close(cmd->fd_out, data);
				w_execve(path, cmd->args, data->env_tab, data);
			}
		}
		exit(1); // TODO: CHECK ERROR
	}
	else // PARENT PROCESS
	{
		if (cmd->fd_in > 2)
			w_close(cmd->fd_in, data);
		if (cmd->fd_out > 2)
			w_close(cmd->fd_out, data);
	}
}

static void	assign_pipe_fds(t_ast *node, int fd_in, int fd_out)
{
	if (!node)
		return ;
	if (node->type == CMD)
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
	if (pipe->left->type == CMD)
		pipe->left->command.fd_out = fd[1];
	else if (pipe->left->type == PIPE)
		assign_pipe_fds(pipe->left, -1, fd[1]);
	if (pipe->right->type == CMD)
		pipe->right->command.fd_in = fd[0];
	else if (pipe->right->type == PIPE)
		assign_pipe_fds(pipe->right, fd[0], -1);
	handle_ast(pipe->left, data, fd);
	close(fd[1]); // w_close crash
	handle_ast(pipe->right, data, fd);
	close(fd[0]); // w_close crash
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
	if (node && (node->type == REDIR_IN || node->type == REDIR_OUT
			|| node->type == REDIR_APPEND || node->type == HERE_DOC))
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
	else if (node->type == CMD)
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
		printf("Parent: enfant avec PID %d terminé, status = %d\n", wpid,
			status);
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
