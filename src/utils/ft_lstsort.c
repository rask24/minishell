/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:42:55 by yliu              #+#    #+#             */
/*   Updated: 2024/10/08 20:16:25 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	update_head_node(t_list **list, t_list *b)
{
	*list = b;
}

static void	swap(t_list **list, t_list *a, t_list *b)
{
	t_list	*a_before;
	t_list	*b_before;

	a_before = ft_lst_before(*list, a);
	b_before = ft_lst_before(*list, b);
	if (a_before)
		a_before->next = b;
	a->next = b->next;
	if (b_before == a)
		b->next = a;
	else
	{
		b->next = a->next;
		b_before->next = a;
	}
	if (a_before == NULL)
		update_head_node(list, b);
}

void	ft_lstsort(t_list **list, t_cmp cmp)
{
	t_list	*curr_p;
	t_list	*next_p;
	bool	is_sorted;

	if (list == NULL || *list == NULL || cmp == NULL)
		return ;
	is_sorted = true;
	while (true)
	{
		curr_p = *list;
		next_p = curr_p->next;
		is_sorted = true;
		while (next_p)
		{
			if (cmp(curr_p, next_p))
			{
				swap(list, curr_p, next_p);
				is_sorted = false;
			}
			curr_p = next_p;
			next_p = next_p->next;
		}
		if (is_sorted)
			break ;
	}
}
