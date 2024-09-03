/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:35:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/03 18:42:44 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "utils.h"

char	*ft_xstrndup(const char *s, size_t n)
{
	char	*dup;

	dup = ft_strndup(s, n);
	if (dup == NULL)
	{
		print_error("ft_strndup", "cannot allocate memory");
		exit(EXIT_FAILURE);
	}
	return (dup);
}
