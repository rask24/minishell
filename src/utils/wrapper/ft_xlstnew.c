/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:45:00 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/03 18:46:04 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "utils.h"

t_list	*ft_xlstnew(void *content)
{
	t_list	*lst;

	lst = ft_lstnew(content);
	if (lst == NULL)
	{
		print_error("ft_lstnew", "cannot allocate memory");
		exit(EXIT_FAILURE);
	}
	return (lst);
}
