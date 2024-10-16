/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:20:28 by yliu              #+#    #+#             */
/*   Updated: 2024/10/13 00:37:38 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static bool	is_empty_string_content(t_list *node, void *param)
{
	(void)param;
	return (!ft_strcmp(node->content, ""));
}

static void	append_element_to_last(t_list **list, t_list *curr)
{
	char	*tmp;

	if (*list == NULL)
		ft_lstadd_back(list, ft_xlstnew(ft_xstrdup(curr->content)));
	else
	{
		tmp = ft_xstrjoin(ft_lstlast(*list)->content, curr->content);
		free(ft_lstlast(*list)->content);
		ft_lstlast(*list)->content = tmp;
	}
}

t_list	*normalize_list(t_list *curr)
{
	t_list	*list;
	bool	combine;

	list = NULL;
	combine = false;
	while (curr)
	{
		if (curr->content == NULL)
			combine = true;
		else
		{
			if (combine)
			{
				append_element_to_last(&list, curr);
				combine = false;
			}
			else
				ft_lstadd_back(&list, ft_xlstnew(ft_xstrdup(curr->content)));
		}
		curr = curr->next;
	}
	ft_lstremove_if(&list, is_empty_string_content, NULL, free);
	return (list);
}
