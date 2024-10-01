/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:45:09 by yliu              #+#    #+#             */
/*   Updated: 2024/10/01 19:11:19 by yliu             ###   ########.fr       */
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

static bool wildcard_lazy_match(const char *file_name, const char *wildcard_exp)
{
	if (*wildcard_exp == '\0')
		return (*file_name == '\0');
	if (*wildcard_exp == '*')
	{
		while (*file_name)
		{
			if (wildcard_lazy_match(file_name, wildcard_exp + 1))
				return (true);
			file_name++;
		}
		return (wildcard_lazy_match(file_name, wildcard_exp + 1));
	}
	if (*file_name == '\0')
		return (false);
	if (*wildcard_exp == *file_name)
		return (wildcard_lazy_match(file_name + 1, wildcard_exp + 1));
	return (false);
}

static bool should_remove(t_list *file, void *wildcard_exp)
{
	return (!wildcard_lazy_match(file->content, wildcard_exp));
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
