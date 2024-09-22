/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_identifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:24:56 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 23:21:33 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_identifier(const char *input)
{
	if (!(ft_isalpha(*input) || *input == '_'))
		return (false);
	while (*input)
	{
		if (!(ft_isalnum(*input) || *input == '_'))
			return (false);
		input++;
	}
	return (true);
}
