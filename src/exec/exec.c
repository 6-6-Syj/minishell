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

#include "command.h"
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

void	handle_ast(t_ast *node, t_data *data, int *fd)
{
	if (!node)
		return ;
	// if (node && node->type == CMD)
	// {
	// 	ft_printf("┌───────── Command Info ────────┐\n");
	// 	ft_printf("│\tCommand: %s\t\t│\n", node->command.args[0]);
	// 	ft_printf("│\tInput FD: %d\t\t│\n", node->command.fd_in);
	// 	ft_printf("│\tOutput FD: %d\t\t│\n", node->command.fd_out);
	// 	ft_printf("└───────────────────────────────┘\n");
	// }
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

/*
	WIFEXITED(status) : Vrai si le processus fils s'est terminé normalement (par exemple,
		avec exit() ou return).

	WEXITSTATUS(status) : Si WIFEXITED est vrai,
		retourne le code de sortie du processus fils (la valeur passée à exit() ou return).

	WIFSIGNALED(status) : Vrai si le processus fils a été terminé par un signal.

	WTERMSIG(status) : Si WIFSIGNALED est vrai,
		retourne le numéro du signal qui a tué le processus.

	WIFSTOPPED(status) : Vrai si le processus fils a été stoppé (par exemple,
		par SIGSTOP).

	WSTOPSIG(status) : Si WIFSTOPPED est vrai,
		retourne le numéro du signal qui a stoppé le processus.

 */

static void	wait_process(void)
{
	int		status;
	pid_t	wpid;

	while ((wpid = wait(&status)) > 0)
	{
		ft_printf("\033[0;32m\033[1m");
		if (WIFEXITED(status))
			ft_printf("Child PID %d ended normally with status %d\n", wpid,
				WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			ft_printf("Child PID %d was killed by signal %d\n", wpid,
				WTERMSIG(status));
		else
			ft_printf("Child PID %d ended with status %d\n", wpid, status);
		ft_printf("\033[0m");
	}
}

void	exec_ast(t_ast *node, t_data *data)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (!node)
		exit_error(data); // TODO: CHECK ERROR
	if (node->type == CMD && is_builtin(node->command.args[0]))
		data->err = exec_builtin(&node->command, &data->env, data);
	else
	{
		handle_ast(node, data, fd);
		wait_process();
	}
}
