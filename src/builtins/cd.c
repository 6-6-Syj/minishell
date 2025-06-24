/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:21:04 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:50:38 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "errno.h"
#include "libft.h"
#include <string.h>
#include <sys/stat.h>

int	is_symlink(const char *path)
{
	struct stat	sb;

	return (lstat(path, &sb) == 0 && S_ISLNK(sb.st_mode));
}

static int	get_oldpwd(char *oldpwd)
{
	if (!getcwd(oldpwd, PATH_MAX))
		return (-1);
	return (0);
}

static int	w_cd(char *target, t_data *data)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];
	int		getcwd_failed;

	getcwd_failed = 0;
	ft_bzero(oldpwd, PATH_MAX);
	ft_bzero(newpwd, PATH_MAX);
	// Debug: afficher l'état initial
	printf("DEBUG: Avant getcwd initial\n");
	// Essayer d'obtenir le répertoire courant, mais ne pas échouer si ça rate
	if (get_oldpwd(oldpwd) != 0)
	{
		getcwd_failed = 1;
		printf("DEBUG: getcwd initial a échoué\n");
		// On continue quand même le cd
	}
	else
	{
		printf("DEBUG: getcwd initial réussi: %s\n", oldpwd);
	}
	printf("DEBUG: Avant chdir vers %s\n", target);
	// Faire le chdir
	if (chdir(target) == -1)
	{
		printf("DEBUG: chdir a échoué\n");
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	printf("DEBUG: chdir réussi, maintenant getcwd après chdir\n");
	// Le chdir a réussi, maintenant gérer PWD/OLDPWD
	if (!getcwd(newpwd, PATH_MAX))
	{
		printf("DEBUG: getcwd après chdir a échoué - errno: %d (%s)\n", errno,
			strerror(errno));
		// Afficher l'erreur pour getcwd après chdir mais retourner 0 car le cd a réussi
		ft_putstr_fd("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
			STDERR_FILENO);
		// Le cd a réussi même si getcwd échoue, donc err = 0
	}
	else
	{
		printf("DEBUG: getcwd après chdir réussi: %s\n", newpwd);
	}
	// Mettre à jour les variables d'environnement même si getcwd a échoué
	if (!getcwd_failed)
	{
		printf("DEBUG: Mise à jour OLDPWD vers: %s\n", oldpwd);
		set_env_var(data, "OLDPWD", oldpwd);
	}
	if (newpwd[0] != '\0') // Si on a réussi à obtenir le nouveau pwd
	{
		printf("DEBUG: Mise à jour PWD vers: %s\n", newpwd);
		set_env_var(data, "PWD", newpwd);
	}
	data->err = 0; // Le cd a réussi
	return (0);
}

// Need to use set_env_var()
static int	cd_oldpwd(t_data *data)
{
	char		*oldpwd;
	struct stat	sb;

	printf("DEBUG: cd_oldpwd appelé\n");
	oldpwd = get_env_var(data, "OLDPWD");
	printf("\n\nOLDPWD = %s\n\n", oldpwd);
	if (!oldpwd)
	{
		printf("DEBUG: OLDPWD pas défini\n");
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	printf("DEBUG: OLDPWD = %s\n", oldpwd);
	// Vérifier si le répertoire OLDPWD existe encore
	if (stat(oldpwd, &sb) == -1)
	{
		printf("DEBUG: stat() a échoué pour %s - errno: %d (%s)\n", oldpwd,
			errno, strerror(errno));
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(oldpwd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		printf("DEBUG: %s n'est pas un répertoire\n", oldpwd);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(oldpwd, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	printf("DEBUG: stat() réussi, appel de w_cd\n");
	if (w_cd(oldpwd, data) == 0)
	{
		ft_putstr_fd(oldpwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (data->err);
}

static int	cd_home(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(current->key, "HOME"))
			return (w_cd(current->value, data));
		current = current->next;
	}
	ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	data->err = 1;
	return (data->err);
}

int	ft_cd(t_command *cmd, t_data *data)
{
	int	i;

	i = 1;
	while (cmd && cmd->args[i])
		i++;
	if (i == 1)
		return (cd_home(data));
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		data->err = 1;
		return (data->err);
	}
	if (!ft_strcmp(cmd->args[1], "-"))
		return (cd_oldpwd(data));
	return (w_cd(cmd->args[1], data));
}
