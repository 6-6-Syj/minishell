/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:43:41 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 17:24:43 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "command.h"
# include "data.h"
# include "env.h"
# include <linux/limits.h>
# include <unistd.h>

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_env		t_env;
typedef struct s_data		t_data;
typedef struct s_command	t_command;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
int							is_builtin(char *cmd);
int							exec_builtin(t_command *command, t_env **env_lst,
								t_data *data);

int							ft_cd(t_command *cmd, t_data *data);

/* export */
int							handle_export(t_command *cmd, t_env **env_lst,
								t_data *data);
/* print_export */
int							print_export(t_env *env_lst, t_data *data);
/* pint_export_utils */
void						free_copy_env_lst(t_env *copy_env_lst);
void						sort_env_list(t_env *env_lst);

int							handle_unset(t_command *cmd, t_env **env_lst,
								t_data *data);
int							ft_env(t_env *env_lst);
int							ft_pwd(t_data *data);
int							ft_echo(t_command *cmd);

long long					ft_atoll_shell(const char *str);
int							ft_exit(t_command *cmd, t_data *data);

#endif
