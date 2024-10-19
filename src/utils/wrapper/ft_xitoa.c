/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:39:13 by yliu              #+#    #+#             */
/*   Updated: 2024/10/17 17:55:22 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_xitoa(int n)
{
	char	*str;

	str = ft_itoa(n);
	if (str == NULL)
	{
		print_error("ft_itoa", "cannot allocate memory");
		exit(EXIT_FAILURE);
	}
	return (str);
}
