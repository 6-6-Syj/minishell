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
# include "libft.h"
# include <stdio.h>
# include <sys/wait.h>

/****************************************************************************/
/*                                DEFINE									*/
/****************************************************************************/

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_data	t_data;
typedef struct s_ast	t_ast;

typedef struct s_pipe
{
	int					in_prev;
	int					in_current;
	int					out_prev;
	int					out_current;
	int fds[2]; // stock fds of current pipe
}						t_pipe;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
int						handle_ast(t_ast *node, t_data *data, int *fd);
int						exec_ast(t_ast *node, t_data *data);

void					w_access(char *path, t_data *data);
void					w_execve(char *path, char **cmds, char **env,
							t_data *data);
void					w_close(int fd, t_data *data);

void					w_pipe(int *fd, t_data *data);
void					w_dup2(int old, int new, t_data *data);
int						w_fork(t_data *data);
void					redir_out(t_data *data, int *fd);
void					redir_in(t_data *data, int *fd);

char					*get_path(char *cmd, t_data *data);
void					*free_strs(char **strs);

#endif
