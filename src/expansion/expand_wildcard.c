/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:45:09 by yliu              #+#    #+#             */
/*   Updated: 2024/10/01 18:51:28 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"
#include <dirent.h>

static char	**convert_list_to_char_array(t_list *list)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_xmalloc(sizeof(char *) * (ft_lstsize(list) + 1));
	while (list)
	{
		array[i] = ft_xstrdup(list->content);
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

static t_list	*initialize_files(t_ctx *ctx)
{
	t_list			*files;
	DIR				*tmp;
	struct dirent	*dp;

	(void)ctx;
	files = NULL;
	tmp = opendir("./");
	while (true)
	{
		dp = readdir(tmp);
		if (dp == NULL)
			break ;
		if (ft_strcmp(dp->d_name, ".") == 0 || ft_strcmp(dp->d_name, "..") == 0)
			continue ;
		ft_lstadd_back(&files, ft_xlstnew(ft_xstrdup(dp->d_name)));
	}
	closedir(tmp);
	return (files);
}

static bool should_remove(t_list *node, void *wildcard_exp1)
{
	const char *file_name;

	char *wildcard_exp = (char *)wildcard_exp1;
	file_name = node->content;
	while (*wildcard_exp)
	{
		if (*wildcard_exp == '*')
		{
			if (*(wildcard_exp + 1) == '\0')
				return (false);
			while (*file_name && *file_name != *(wildcard_exp + 1))
				file_name++;
			if (*file_name == '\0')
				return (true);
			wildcard_exp++;
		}
		else if (*wildcard_exp != *file_name)
			return (true);
		wildcard_exp++;
		file_name++;
	}
	if (*file_name != '\0')
		return (true);
	return (false);
}

char	**expand_wildcard(char *wildcard_exp, t_ctx *ctx)
{
	t_list	*files;
	char	**array;

	files = initialize_files(ctx);
	ft_lstremove_if(&files, should_remove, wildcard_exp, free);
	if (files == NULL)
			return (convert_list_to_char_array(ft_lstnew(ft_xstrdup(wildcard_exp))));
	array = convert_list_to_char_array(files);
	return (array);
}
