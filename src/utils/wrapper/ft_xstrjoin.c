/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:15:39 by yliu              #+#    #+#             */
/*   Updated: 2024/09/18 20:28:00 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_xstrjoin(const char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (ret == NULL)
	{
		print_error("ft_strjoin", "cannot allocate memory");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
