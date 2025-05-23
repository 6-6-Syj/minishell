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

static int	exec_command(t_ast *cmd, t_data *data)
{
	char	*path;

	// int		fd;
	// fd = 3;
	path = NULL;
	if (cmd && cmd->args)
		path = get_path(cmd->args[0], data);
	if (!path)
		return (-42); // TODO: CHECK ERROR
	w_access(path, data);
	// while (fd < 1024)
	// 	w_close(fd++, data);
	w_execve(path, cmd->args, data->env_tab, data);
	return (0); // UNREACHABLE
}

static int	exec_fork_command(t_ast *cmd, t_data *data, int *fd)
{
	pid_t	pid;
	int		status;

	pid = w_fork(data);
	if (pid == 0) // CHILD
		return (exec_command(cmd, data));
	else if (cmd && cmd->right)
		return (handle_ast(cmd->right, data, fd));
	else // PARENT
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status)); // TODO: CHECK IT
	}
}

static int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

static int	handle_exec(t_ast *cmd, t_data *data, int *fd)
{
	if (is_builtin(cmd->args[0]))
		return (exec_builtin(&data->env, data, cmd->args[0]));
	else if (cmd && !cmd->fork)
		return (exec_command(cmd, data));
	else
		return (exec_fork_command(cmd, data, fd));
	return (0); // UNREACHABLE
}

static int	handle_and_or(t_ast *node, t_data *data, int *fd)
{
	int	ret;

	ret = handle_ast(node->left, data, fd);
	if (node->type == AND)
	{
		if (ret == 0)
			ret = handle_ast(node->right, data, fd);
	}
	else // type == OR
	{
		if (ret != 0)
			ret = handle_ast(node->right, data, fd);
	}
	return (ret);
}

static int	handle_pipe(t_ast *pipe_node, t_data *data, int *fd)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	w_pipe(fd, data);
	pid_left = w_fork(data);
	if (pid_left == 0) // CHILD
	{
		redir_out(data, fd);
		return (handle_ast(pipe_node->left, data, fd));
	}
	else // PARENT
	{
		if (pipe_node && pipe_node->right && pipe_node->right->type == COMMAND)
		{
			pid_right = w_fork(data);
			if (pid_right == 0) // CHILD
			{
				redir_in(data, fd);
				return (handle_ast(pipe_node->right, data, fd));
			}
			// PARENT
			w_close(fd[0], data); // close pipe in
			w_close(fd[1], data); // close pipe out
			waitpid(pid_right, &status_right, 0);
			waitpid(pid_left, &status_left, 0);
			return (status_right); // TODO: CHECK THIS
		}
		return (handle_ast(pipe_node->right, data, fd));
	}
}

int	handle_ast(t_ast *node, t_data *data, int *fd)
{
	if (node && (node->type == AND || node->type == OR))
		return (handle_and_or(node, data, fd));
	else if (node && node->type == PIPE)
		return (handle_pipe(node, data, fd));
	// else if (node && (node->type == REDIR_IN_TRUNC
	// || node->type == REDIR_OUT_TRUNC
	// 	|| node->type == REDIR_OUT_APPEND || node->type == HERE_DOC))
	// {
	// 	// Handle redirect stdin/out
	// 	// Ouvrir le fichier approprié en fonction du type de redirection
	// 	// Dupliquer les descripteurs de fichiers standards
	// 	// Fermer les descripteurs de fichiers inutiles
	// 	// Si un sous-arbre droit existe,
	// 	// cela signifie qu'il y a d'autres redirections à faire
	// 	// Si tout se passe bien à droite,
	// 	// continuer à gauche ou exécuter la commande
	// 	// Si problème à droite, retourner le code d'erreur du sous-arbre droit
	// 	return (-42);
	// }
	else // (node->type == COMMAND)
	{
		// if (node->right)
		// 	return (handle_ast(node->right, data, fd));
		return (handle_exec(node, data, fd));
	}
	// Retourner le code de sortie approprié
}

int exec_ast(t_ast *node, t_data *data)
{
	// t_pipe	*pipe;
	int		ret;

	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	ret = handle_ast(node, data, fd);
	// close all fd
	return (ret);
}
