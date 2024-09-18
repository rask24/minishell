/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:40:41 by yliu              #+#    #+#             */
/*   Updated: 2024/09/18 20:26:00 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	destroy_token_helper(void *content)
{
	free(((t_token *)content)->value);
	free(content);
}

void	destroy_token(t_token_list *token)
{
	ft_lstdelone(token, destroy_token_helper);
}

void	destroy_token_list(t_token_list *token_list)
{
	ft_lstclear(&token_list, destroy_token_helper);
}
