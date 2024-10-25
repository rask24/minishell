/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:39:13 by yliu              #+#    #+#             */
/*   Updated: 2024/10/25 19:49:06 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
