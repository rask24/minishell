/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:54:29 by yliu              #+#    #+#             */
/*   Updated: 2024/10/24 12:54:27 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_cd_internal.h"

static void	process_two_dots(char **original_path, char *normalized_path,
								char **cursor)
{
	if (*cursor - 1 != normalized_path)
	{
		(*cursor)--;
		(*cursor)--;
		while ((*cursor) > normalized_path && **cursor != '/')
			(*cursor)--;
		(*cursor)++;
	}
	*original_path += 3;
}

static void	process_slashes(char **original_path, char **cursor)
{
	while (*(*original_path + 1) != '\0' && *(*original_path + 1) == '/')
		(*original_path)++;
	**cursor = **original_path;
	(*original_path)++;
	(*cursor)++;
}

char	*normalize_path(char *original_path)
{
	char	*normalized_path;
	char	*cursor;

	normalized_path = ft_xmalloc(sizeof(char) * ft_strlen(original_path) + 1);
	cursor = normalized_path;
	while (*original_path != '\0')
	{
		if (ft_strncmp(original_path, "./", 2) == 0)
			original_path += 2;
		else if (ft_strncmp(original_path, "../", 3) == 0)
			process_two_dots(&original_path, normalized_path, &cursor);
		else if (*original_path == '/')
			process_slashes(&original_path, &cursor);
		else
		{
			*cursor = *original_path;
			original_path++;
			cursor++;
		}
	}
	*cursor = '\0';
	return (normalized_path);
}
