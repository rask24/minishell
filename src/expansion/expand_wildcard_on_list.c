/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_on_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:45:09 by yliu              #+#    #+#             */
/*   Updated: 2024/10/02 15:43:42 by yliu             ###   ########.fr       */
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

static t_list	*initialize_files(void)
{
	t_list			*files;
	DIR				*tmp;
	struct dirent	*dp;

	files = NULL;
	tmp = opendir("./");
	if (tmp == NULL)
		return (NULL);
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

static bool	should_remove(t_list *file, void *wildcard_exp)
{
	return (!wildcard_lazy_match(file->content, wildcard_exp));
}

static char	**expand_wildcard(char *wildcard)
{
	t_list	*files;
	char	**array;

	files = initialize_files();
	if (files == NULL)
		return (NULL);
	ft_lstremove_if(&files, should_remove, wildcard, free);
	if (files == NULL)
		array = convert_list_to_char_array(ft_xlstnew(ft_xstrdup(wildcard)));
	else
		array = convert_list_to_char_array(files);
	ft_lstclear(&files, free);
	return (array);
}

t_list	*expand_wildcard_on_list(t_list *list)
{
	t_list	*curr;
	char	**wildcard_expanded_words;
	t_list	*result;

	curr = list;
	result = NULL;
	while (curr)
	{
		wildcard_expanded_words = expand_wildcard(curr->content);
		while (*wildcard_expanded_words)
		{
			ft_lstadd_back(&result, ft_xlstnew(*wildcard_expanded_words));
			wildcard_expanded_words++;
		}
		curr = curr->next;
	}
	ft_lstclear(&list, free);
	return (result);
}
