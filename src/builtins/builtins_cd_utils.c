/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:54:29 by yliu              #+#    #+#             */
/*   Updated: 2024/10/06 14:29:09 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cd_internal.h"

static void	process_two_dots(char **original_path, char *altered_path,
								char **cursor)
{
	if (*cursor - 1 != altered_path)
	{
		(*cursor)--;
		(*cursor)--;
		while ((*cursor) > altered_path && **cursor != '/')
			(*cursor)--;
		(*cursor)++;
	}
	*original_path += 3;
}

char	*remove_long_path(char *original_path)
{
	char	*altered_path;
	char	*cursor;

	altered_path = ft_xmalloc(sizeof(char) * ft_strlen(original_path) + 1);
	cursor = altered_path;
	while (*original_path != '\0')
	{
		if (ft_strncmp(original_path, "./", 2) == 0)
			original_path += 2;
		else if (ft_strncmp(original_path, "../", 3) == 0)
			process_two_dots(&original_path, altered_path, &cursor);
		else
		{
			*cursor = *original_path;
			original_path++;
			cursor++;
		}
	}
	*cursor = '\0';
	return (altered_path);
}
