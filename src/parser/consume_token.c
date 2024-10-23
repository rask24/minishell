/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:55:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/23 14:58:11 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "token.h"

bool	consume_token(t_token_list **cur_token)
{
	if (*cur_token == NULL)
		return (false);
	*cur_token = (*cur_token)->next;
	return (true);
}
