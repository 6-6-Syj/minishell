/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:43:41 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/06 03:01:51 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "env.h"
# include <linux/limits.h>
# include <unistd.h>
// # include <stdbool.h>

/****************************************************************************/
/*                                DEFINE									*/
/****************************************************************************/
// # define C_SPACE	' '
// # define C_SIMPLE_QUOTE '\''
// # define C_DOUBLE_QUOTE '\"'

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/
// typedef enum e_type
// {
// 	TYPE_PARENTHESE,
// 	TYPE_OPERATOR,
// 	TYPE_PIPE,
// 	TYPE_REDIRECTION,
// 	TYPE_COMMAND,
// 	TYPE_EXPAND,
// 	TYPE_QUOTE,
// 	TYPE_SPACE,
// } t_type;

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_env	t_env;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
void					free_split(char **split);
int						ft_buitins(t_env **env_lst, char *input);

int						handle_cd(t_env *env, char *input);
int						handle_export(t_env **env_lst, char *input);
int						print_export(t_env *env_lst);
int						handle_unset(t_env **env_lst, char *input);
int						ft_env(t_env *env_lst);
int						ft_pwd(void);

#endif
