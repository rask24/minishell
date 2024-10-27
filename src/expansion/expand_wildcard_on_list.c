/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_on_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:45:09 by yliu              #+#    #+#             */
/*   Updated: 2024/10/27 11:59:16 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"
#include <dirent.h>

static t_list	*initialize_files(void)
{
	t_list			*files;
	DIR				*cur_dir;
	struct dirent	*dp;

	files = NULL;
	cur_dir = opendir("./");
	if (cur_dir == NULL)
		return (NULL);
	while (true)
	{
		dp = readdir(cur_dir);
		if (dp == NULL)
			break ;
		if (ft_strcmp(dp->d_name, ".") == 0 || ft_strcmp(dp->d_name, "..") == 0)
			continue ;
		ft_lstadd_back(&files, ft_xlstnew(ft_xstrdup(dp->d_name)));
	}
	closedir(cur_dir);
	return (files);
}

static bool	simple_cmp(t_list *a, t_list *b)
{
	return (ft_strcmp(a->content, b->content) > 0);
}

static bool	should_remove(t_list *file, void *wildcard_exp)
{
	return (!wildcard_lazy_match(file->content, wildcard_exp));
}

static bool	should_remove_hidden(t_list *file, void *wildcard_exp)
{
	(void)wildcard_exp;
	return (((char *)(file->content))[0] == '.');
}

t_list	*expand_wildcard_on_list(t_list *list)
{
	char	*wildcard_exp;
	t_list	*files;
	t_list	*curr;
	t_list	*result;

	curr = list;
	result = NULL;
	while (curr)
	{
		wildcard_exp = curr->content;
		files = initialize_files();
		if (wildcard_exp[0] != '.')
			ft_lstremove_if(&files, should_remove_hidden, wildcard_exp, free);
		ft_lstremove_if(&files, should_remove, wildcard_exp, free);
		ft_lstsort(&files, simple_cmp);
		if (files == NULL)
			files = ft_xlstnew(ft_xstrdup(wildcard_exp));
		ft_lstadd_back(&result, files);
		curr = curr->next;
	}
	return (result);
}
