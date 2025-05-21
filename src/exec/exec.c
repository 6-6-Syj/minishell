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

static char	**split_path(char *cmd, t_env *env, t_data *data)
{
	char	**paths;

	paths = NULL;
	if (!cmd)
		return (NULL);
	while (env->next && ft_strcmp("PATH=", env->key) != 0)
		env = env->next;
	paths = ft_split(env->value, ':');
	if (!paths)
		exit_error(data);
	return (paths);
}

static char	*get_path(char *cmd, t_env *env, t_data *data)
{
	char	*buff;
	char	*path;
	char	**paths;
	int		i;

	paths = split_path(cmd, env, data);
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

static void	handle_pipe(t_ast *pipe_node, t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit_error(data);
	pipe_node->fd.read_prev = -1;
	pipe_node->fd.read_current = fd[0];
	pipe_node->fd.write_prev = -1;
	pipe_node->fd.write_current = fd[1];
}

static void	redirection(t_ast *cmd, t_data *data)
{
	if (dup2(cmd->fd.read_current, STDIN_FILENO) == -1)
		exit_error(data);
	if (dup2(cmd->fd.write_current, STDOUT_FILENO) == -1)
		exit_error(data);
	if (cmd->fd.read_current != -1)
		close(cmd->fd.read_current);
	if (cmd->fd.read_prev != -1)
		close(cmd->fd.read_prev);
	if (cmd->fd.write_current != -1)
		close(cmd->fd.write_current);
	if (cmd->fd.write_prev != -1)
		close(cmd->fd.write_prev);
}

static int	exec_command(t_ast *cmd, t_data *data, char **env)
{
	pid_t	pid;
	char	*path;

	// check if builtins
	path = get_path(cmd->args[0], data->env, data);
	pid = fork();
	if (pid < 0)
		return ;   // free(data)
	if (pid == 0) // CHILD
	{
		redirection(cmd, data); // close useless fds;
		ft_access(path, data);
		execve(path, cmd->args, env);
		// exit_error(data);
	}
	if (pid > 0) // PARENT
	{
		// close fd
		return ;
	}
}

int handle_ast(t_ast *node, t_data *data, char **env)
{
    // Gestion des opérateurs logiques AND et OR
    // if (node->type == AND)
    // {
    //     // Exécuter le sous-arbre gauche
    //     // Si le sous-arbre gauche réussit (retourne 0), exécuter le sous-arbre droit
    //     // Sinon, retourner l'erreur
    // }
    // if (node->type == OR)
    // {
    //     // Exécuter le sous-arbre gauche
    //     // Si le sous-arbre gauche échoue (retourne une erreur), exécuter le sous-arbre droit
    //     // Sinon, retourner le succès
    // }
    if (node->type == PIPE)
    {
        // Créer un pipe pour la communication entre les processus
        // Fork pour exécuter le sous-arbre gauche dans le processus enfant
        // Dans le processus enfant, exécuter le sous-arbre gauche
        // Dans le processus parent, exécuter le sous-arbre droit
        handle_pipe(node, data); // Gérer la création du pipe et la redirection des descripteurs de fichiers
        if (node->right->type == PIPE)
            return (handle_ast(node->right, data, env));
        // Si le sous-arbre droit est aussi un pipe, continuer à le traiter
        return (handle_ast(node->left, data, env));
    }
    else if (node->type == REDIR_IN_TRUNC || node->type == REDIR_OUT_TRUNC || node->type == REDIR_OUT_APPEND || node->type == HERE_DOC)
    {
        // Gérer les redirections d'entrée/sortie
        // Ouvrir le fichier approprié en fonction du type de redirection
        // Dupliquer les descripteurs de fichiers standards
        // Fermer les descripteurs de fichiers inutiles
        // Si un sous-arbre droit existe, cela signifie qu'il y a d'autres redirections à faire
        // Si tout se passe bien à droite, continuer à gauche ou exécuter la commande
        // Si problème à droite, retourner le code d'erreur du sous-arbre droit
        if (node->right)
            return (handle_ast(node->right, data, env));
    }
    else if (node->type == COMMAND)
    {
        // Exécuter la commande
        // Préparer les arguments et l'environnement
        // Utiliser execve ou une fonction similaire pour exécuter la commande
        exec_command(node, data, env);
        // Si un sous-arbre droit existe, le traiter
        // Si un sous-arbre gauche existe, le traiter
    }
    // Retourner le code de sortie approprié
}


// use data->err for status code ?
int	handle_ast(t_ast *node, t_data *data, char **env)
{
	// if (node->type == AND)
	// {
	// }
	// if (node->type == OR)
	// {
	// }
	if (node->type == PIPE)
	{
		// je fork pour a gauche : if pid = 0 : exec_ast(left)
		handle_pipe(node, data); // pipe(); redir, close fd...
		if (node->right->type == PIPE)
			return (handle_ast(node->right, data, env));
		// pipe need fork, parent goes right
		return (handle_ast(node->left, data, env));
	}
	else if (node->type == REDIR_IN_TRUNC || REDIR_OUT_TRUNC || REDIR_OUT_APPEND
		|| HERE_DOC)
	{
		// jopen je dup je close
		// si un right existe : cést que ya dáutres redirs a faire
		// if (pas de prob a droite)
		// on continue a gauche // on execute la commande
		// si pb a droite :
		// peut etre qu on return juste léxit code de rihgt
		if (node->right)
			return (handle_ast(node->right, data, env));
	}
	else if (node->type == COMMAND)
	{
		// return (exec_command(node, data, env));
		exec_command(node, data, env);
		// if (node->right)
		// 	return (handle_ast(node->right, data, env));
		// if (node->left)
		// 	return (handle_ast(node->left, data, env));
	}
	// return (handle_ast()); // fork();
}
