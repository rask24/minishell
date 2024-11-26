/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:39:12 by yliu              #+#    #+#             */
/*   Updated: 2024/11/25 18:48:36 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstinsert(t_list **lst, t_list *trg, t_list *insert)
{
	t_list	*trg_prev;

	if (lst == NULL || insert == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = insert;
		return ;
	}
	if (trg == NULL)
	{
		ft_lstlast(*lst)->next = insert;
		return ;
	}
	else
	{
		ft_lstlast(insert)->next = trg;
		trg_prev = ft_lst_before(*lst, trg);
		if (trg_prev == NULL)
			*lst = insert;
		else
			trg_prev->next = insert;
	}
}
