/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-18 21:32:48 by jmagand           #+#    #+#             */
/*   Updated: 2025-08-18 21:32:48 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <sys/stat.h>
#include <string.h>

bool	is_symlink(const char *path)
{
	struct stat	sb;

	if (lstat(path, &sb) == 0 && S_ISLNK(sb.st_mode))
		return (true);
	else
		return (false);
}
