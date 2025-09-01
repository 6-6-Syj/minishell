/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 18:36:03 by jmagand           #+#    #+#             */
/*   Updated: 2025-05-09 18:36:03 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "ast.h"

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/
typedef enum e_path_status	t_path_status;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_data		t_data;
typedef struct s_ast		t_ast;
typedef struct s_fd_backup	t_fd_backup;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
/* handle_end_process */
int							wait_all_processes(t_data *data);

/* exec */
void						handle_ast(t_ast *node, t_data *data, int *fd);
void						exec_ast(t_ast *node, t_data *data);
void						exec_and_restore_fd(t_fd_backup *backup,
								t_command *cmd, t_data *data);

/* path */
char						*find_path(char **paths, char *cmd);
char						*resolve_command_path(char *cmd, t_data *data,
								t_path_status *status);

/* path_utils */
int							is_absolute_or_relative_path(char *cmd);

#endif
