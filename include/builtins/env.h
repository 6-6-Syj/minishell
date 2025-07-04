/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabuchhe <dabuchhe@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:07:21 by jmagand           #+#    #+#             */
/*   Updated: 2025/05/08 19:28:00 by dabuchhe         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/****************************************************************************/
/*                                INCLUDE									*/
/****************************************************************************/
# include "builtins.h"
# include "data.h"
# include "error.h"
# include "libft.h"
# include "status.h"
# include <unistd.h>

/****************************************************************************/
/*                                DEFINE									*/
/****************************************************************************/

/****************************************************************************/
/*                                ENUM										*/
/****************************************************************************/

/****************************************************************************/
/*                                STRUCT									*/
/****************************************************************************/
typedef struct s_env
{
	t_status		err;
	char			*key;
	char			*value;
	bool			print_env;
	bool			print_exp;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

/****************************************************************************/
/*                                FUNCTIONS									*/
/****************************************************************************/
bool				is_set_env(t_env *new_env, char *env_line);
t_env				*get_last_env(t_env *lst);
t_env				*add_env_node(t_env **env_lst);

void				init_env_i(t_data *data);
void				init_env(t_data *data, char **env);

void				print_env_tab(char **env_tab);
char				**update_env_tab(t_data *data);
void				free_env_lst(t_env **env_lst);
void				free_env_tab(t_data *data);

char				*get_env_var(t_data *data, char *key);
int					set_env_var(t_data *data, char *key, char *value);
#endif
