/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:44:37 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 12:17:33 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstreplace(t_list **lst, t_list *node, t_list *new_node)
{
	if (lst == NULL || *lst == NULL || node == NULL || new_node == NULL)
		return ;
	ft_lstinsert(lst, node, new_node);
	ft_lstremove(lst, node, free);
}
