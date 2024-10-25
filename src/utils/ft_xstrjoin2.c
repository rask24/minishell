/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrjoin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:51:10 by yliu              #+#    #+#             */
/*   Updated: 2024/10/25 19:48:46 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "utils.h"

char	*ft_xstrjoin2(char *s1, const char *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		s1 = ft_xstrdup(s2);
	else
	{
		tmp = ft_xstrjoin(s1, s2);
		free(s1);
		s1 = tmp;
	}
	return (s1);
}
