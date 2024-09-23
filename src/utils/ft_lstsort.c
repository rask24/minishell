/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:42:55 by yliu              #+#    #+#             */
/*   Updated: 2024/09/15 16:24:40 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	swap(t_list *list, t_list *a, t_list *b, t_cmp cmp)
{
	t_list	*a_before;
	t_list	*b_before;
	t_list	*tmp;

	if (cmp(a, b))
	{
		a_before = ft_lst_before(list, a);
		b_before = ft_lst_before(list, b);
		a_before->next = b;
		b_before->next = a;
		tmp = a->next;
		a->next = b->next;
		b->next = tmp;
	}
}

void	ft_lstsort(t_list **list, t_cmp cmp)
{
	t_list	*curr;
	t_list	*next;

	curr = *list;
	while (curr)
	{
		next = curr->next;
		while (next)
		{
			swap(*list, curr, next, cmp);
			next = next->next;
		}
		curr = curr->next;
	}
}
