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

static void	*free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (NULL);
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static void	ft_access(char *path, t_data *data)
{
	if (!path)
	{
		exit_error(data);
		exit(EXIT_FAILURE);
	}
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("Error\nCommand not found\n", 2);
		exit_error(data);
		exit(127);
	}
	if (access(path, X_OK) == -1)
	{
		exit_error(data);
		ft_putstr_fd("Error\nPermission denied\n", 2);
		exit(126);
	}
}

static char	**split_path(char *cmd, t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	if (!cmd)
		return (NULL);
	while (data->env_tab[i])
	{
		if (ft_strncmp("PATH=", data->env_tab[i], 5) == 0)
		{
			paths = ft_split(data->env_tab[i] + 5, ':');
			if (!paths)
				exit_error(data);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static char	*get_path(char *cmd, t_data *data)
{
	char	*buff;
	char	*path;
	char	**paths;
	int		i;

	paths = split_path(cmd, data);
	i = -1;
	while (paths && paths[++i])
	{
		buff = ft_strjoin("/", cmd);
		if (!buff)
			return (NULL);
		path = ft_strjoin(paths[i], buff);
		free(buff);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
		{
			free_strs(paths);
			return (path);
		}
		free(path);
	}
	free_strs(paths);
	return (ft_strdup(cmd));
}

static int	exec_command(t_ast *cmd, t_data *data)
{
	char	*path;

	// check if builtins
	path = get_path(cmd->args[0], data);
	if (!path)
		return (-1);       // TODO: CHECK ERROR
	// redirection(data, fd); // TODO: CHECK ERROR, if ?
	ft_access(path, data);
	execve(path, cmd->args, data->env_tab);
	exit_error(data);
	return (-42); // check
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
	pid_t	pid;

	// Créer un pipe pour la communication entre les processus
	if (pipe(fd) == -1)
		exit_error(data);
	// Fork for exec left
	pid = fork();
	if (pid < 0)
		exit_error(data); // free(data)
	if (pid == 0)         // CHILD
	{
		close(fd[0]); // Close read (useless fd)
		if (dup2(fd[1], STDOUT_FILENO) == -1) // redirect stdout -> pipe
			exit_error(data);
		close(fd[1]); // Close old writing fd
		return (exec_command(pipe_node->left, data));
	}
	else // PARENT
	{
		// TODO: close fd
		close(fd[1]); // Close write (useless fd)
		if (dup2(fd[0], STDIN_FILENO) == -1) // redirect stdin -> pipe
			exit_error(data);
		close(fd[0]); // Close old reading fd
		// waitpid(pid, &status, 0); // Wait for the child
		return (handle_ast(pipe_node->right, data, fd));
	}
}

int	handle_ast(t_ast *node, t_data *data, int *fd)
{
	if (node->type == AND || node->type == OR)
		return (handle_and_or(node, data, fd));
	else if (node->type == PIPE)
		return (handle_pipe(node, data, fd));
	// else if (node->type == REDIR_IN_TRUNC || node->type == REDIR_OUT_TRUNC
	// 	|| node->type == REDIR_OUT_APPEND || node->type == HERE_DOC)
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
	// 	;
	// }
	else // (node->type == COMMAND)
	{
		return (exec_command(node, data));
		if (node->right)
			return (handle_ast(node->right, data, fd));
		if (node->left)
			return (handle_ast(node->left, data, fd));
	}
	// Retourner le code de sortie approprié
}
