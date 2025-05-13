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

// static void free_commands(t_cmds *cmds)
// {
//     t_cmds *current;
//     t_cmds *next;
//     int i;

//     current = cmds;
//     while (current)
//     {
//         next = current->next;
//         free(current->path);
//         i = 0;
//         while (current->cmds[i])
//         {
//             free(current->cmds[i]);
//             i++;
//         }
//         free(current->cmds);
//         free(current);
//         current = next;
//     }
// }

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

static void init_test_commands(t_data *data, char **env)
{
    // Création de commandes de test avec allocation dynamique
    char **ls_cmd = malloc(3 * sizeof(char *));
    char **cat_cmd = malloc(4 * sizeof(char *));
    char **wc_cmd = malloc(2 * sizeof(char *));

    if (!ls_cmd || !cat_cmd || !wc_cmd)
    {
        ft_printf("Error allocating memory for commands\n");
        exit(EXIT_FAILURE);
    }

    ls_cmd[0] = ft_strdup("ls");
    ls_cmd[1] = ft_strdup("-l");
    ls_cmd[2] = NULL;

    cat_cmd[0] = ft_strdup("cat");
    cat_cmd[1] = ft_strdup("-e");
    cat_cmd[2] = ft_strdup("main.c");
    cat_cmd[3] = NULL;

    wc_cmd[0] = ft_strdup("wc");
    wc_cmd[1] = NULL;

    // Ajout des commandes à la liste
    t_cmds *cmd1 = create_cmd(ft_strdup("/usr/bin/ls"), ls_cmd, env);
    t_cmds *cmd2 = create_cmd(ft_strdup("/usr/bin/cat"), cat_cmd, env);
    t_cmds *cmd3 = create_cmd(ft_strdup("/usr/bin/wc"), wc_cmd, env);

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
}

void	prepare_execution(t_data *data, char **env)
{
	t_cmds	*current_cmd;
	pid_t	pid;
	int		status;

	init_test_commands(data, env);

	current_cmd = data->cmds;
	while (current_cmd != NULL)
	{
		ft_printf("current_cmd->cmds = %s\n", current_cmd->cmds[0]);
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
		current_cmd = current_cmd->next;
	}
}
