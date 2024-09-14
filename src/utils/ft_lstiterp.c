/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiterp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:36:46 by yliu              #+#    #+#             */
/*   Updated: 2024/09/09 21:52:48 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstiterp(t_list *lst, void (*f)(void *, void *), void *param)
{
	if (!f || !param)
		return ;
	while (lst)
	{
		f(lst->content, param);
		lst = lst->next;
	}
}
