/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:54:29 by yliu              #+#    #+#             */
/*   Updated: 2024/10/05 22:56:15 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cd_internal.h"

static void	process_two_dots(char **path, char *ans, char **ptr)
{
	if (*ptr - 1 != ans)
	{
		(*ptr)--;
		(*ptr)--;
		while (**ptr != '/')
			(*ptr)--;
		(*ptr)++;
	}
	*path += 3;
}

char	*remove_long_path(char *path)
{
	char	*ans;
	char	*ptr;

	ans = ft_xmalloc(sizeof(char) * ft_strlen(path) + 1);
	ptr = ans;
	while (*path != '\0')
	{
		if (ft_strncmp(path, "./", 2) == 0)
			path += 2;
		else if (ft_strncmp(path, "../", 3) == 0)
			process_two_dots(&path, ans, &ptr);
		else
		{
			*ptr = *path;
			path++;
			ptr++;
		}
	}
	*ptr = '\0';
	return (ans);
}
