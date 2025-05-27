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

#include "command.h"
#include "exec.h"
#include "pipe.h"

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
