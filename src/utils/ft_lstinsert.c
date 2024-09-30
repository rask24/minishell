/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:30:41 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 01:20:50 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstinsert(t_list **lst, t_list *trg, t_list *insert)
{
	if (lst == NULL || *lst == NULL)
		return ;
	if (trg == NULL)
	{
		ft_lstlast(insert)->next = *lst;
		*lst = insert;
		return ;
	}
	ft_lstlast(insert)->next = trg->next;
	trg->next = insert;
}
