/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:45:09 by yliu              #+#    #+#             */
/*   Updated: 2024/10/01 10:49:50 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"
#include <dirent.h>

static char	**convert_t_list_array(t_list *list)
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

char	**expand_wildcard(char *str, t_ctx *ctx)
{
	t_list	*files;
	char	**array;

	(void)str;
	files = initialize_files(ctx);
	array = convert_t_list_array(files);
	return (array);
}
