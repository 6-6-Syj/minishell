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
# include "data.h"
# include "libft.h"
# include "wrappers.h"
# include <stdio.h>
# include <sys/wait.h>

/****************************************************************************/
/*                                DEFINE									*/
/****************************************************************************/

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/
typedef enum e_path_status	t_path_status;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_data		t_data;
typedef struct s_ast		t_ast;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
/* handle_end_process */
int							wait_all_processes(t_pid_list *pids, t_data *data);
void						add_pid(t_pid_list **pids, pid_t pid, bool is_last,
								t_data *data);

/* exec */
void						handle_ast(t_ast *node, t_data *data, int *fd,
								t_pid_list **pids);
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
