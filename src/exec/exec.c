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

static t_cmds *create_cmd(char *path, char **cmds, char **env)
{
    t_cmds *new_cmd;

	new_cmd = malloc(sizeof(t_cmds));
    if (!new_cmd)
        return NULL;
    new_cmd->path = path;
    new_cmd->cmds = cmds;
	new_cmd->env = env;
    new_cmd->next = NULL;
    return (new_cmd);
}

static void	ft_access(t_cmds *last)
{
	if (!last->path)
		exit(EXIT_FAILURE);
	if (access(last->path, F_OK) == -1)
	{
		ft_putstr_fd("Error\nCommand not found\n", 2);
		exit(127);
	}
	if (access(last->path, X_OK) == -1)
	{
		ft_putstr_fd("Error\nPermission denied\n", 2);
		exit(126);
	}
}

static void execute_command(t_cmds *current_cmd)
{
    char **args;
    char **env;
    int i;
	int j;

	i = 0;
	j = 0;
    while (current_cmd->cmds[i])
        i++;
    args = malloc(sizeof(char *) * (i + 1));
    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while (j < i)
	{
        args[j] = current_cmd->cmds[j];
		j++;
	}
    args[j] = NULL;
    env = current_cmd->env;
	ft_access(current_cmd);
    if (execve(current_cmd->path, args, env) == -1)
    {
        perror("execve");
        free(args);
        exit(EXIT_FAILURE);
    }
    // free(args);
}

void	prepare_execution(t_data *data, char **env)
{
	t_cmds	*current_cmd;
	pid_t	pid;
	int		status;

	// Création de commandes de test
    char *wc_cmd[] = {"wc", NULL};
    char *ls_cmd[] = {"ls", "-l", NULL};
	char *cat_cmd[] = {"cat", "-e", "main.c", NULL};

    // Ajout des commandes à la liste
    t_cmds *cmd1 = create_cmd("/usr/bin/wc", wc_cmd, env);
    t_cmds *cmd2 = create_cmd("/usr/bin/ls", ls_cmd, env);
	t_cmds *cmd3 = create_cmd("/usr/bin/cat", cat_cmd, env);

    if (!cmd1 || !cmd2 || !cmd3)
    {
        ft_printf("Error creating commands\n");
        exit(EXIT_FAILURE);
    }

    // Construction de la liste chaînée
    data->cmds = cmd1;
    cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd3->next = NULL;

	current_cmd = data->cmds;
	while (current_cmd != NULL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // CHILD
		{
			execute_command(current_cmd);
			exit(EXIT_SUCCESS);
		}
		else // PARENT
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				ft_printf("Command exited with status %d\n",
					WEXITSTATUS(status));
		}
		ft_printf("current_cmd->cmds = %s\n", current_cmd->cmds[0]);
		current_cmd = current_cmd->next;
	}
}
