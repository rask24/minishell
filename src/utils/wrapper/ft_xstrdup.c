/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:17:18 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/05 18:17:59 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "utils.h"

char	*ft_xstrdup(const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (dup == NULL)
	{
		print_error("ft_strdup", "cannot allocate memory");
		exit(EXIT_FAILURE);
	}
	return (dup);
}
