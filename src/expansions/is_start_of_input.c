/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_start_of_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:24:03 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 16:26:10 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

bool	is_start_of_input_(t_expansion *expansions)
{
	return (expansions->left == expansions->right);
}
