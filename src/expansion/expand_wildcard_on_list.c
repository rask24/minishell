/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_on_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:45:09 by yliu              #+#    #+#             */
/*   Updated: 2024/10/06 16:56:03 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>

#include "expansion_internal.h"

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

static bool	should_remove(t_list *file, void *wildcard_exp)
{
	return (!wildcard_lazy_match(file->content, wildcard_exp));
}

static bool	simple_cmp(t_list *a, t_list *b)
{
	return (ft_strcmp(a->content, b->content) > 0);
}

static t_list	*expand_wildcard(char *wildcard)
{
	t_list	*files;

	files = initialize_files();
	ft_lstsort(&files, simple_cmp);
	ft_lstremove_if(&files, should_remove, wildcard, free);
	if (files == NULL)
		return (ft_xlstnew(ft_xstrdup(wildcard)));
	return (files);
}

t_list	*expand_wildcard_on_list(t_list *list)
{
	t_list	*curr;
	t_list	*wildcard_expanded_words;
	t_list	*result;

	curr = list;
	result = NULL;
	while (curr)
	{
		wildcard_expanded_words = expand_wildcard(curr->content);
		ft_lstadd_back(&result, wildcard_expanded_words);
		curr = curr->next;
	}
	return (result);
}
