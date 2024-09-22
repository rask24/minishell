/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:30:22 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 16:30:35 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

void	construct_expansions(char *input, t_expansion *expansions)
{
	expansions->left = input;
	expansions->right = input;
}
