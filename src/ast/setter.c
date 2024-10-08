/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 23:14:33 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/05 23:15:51 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	set_file_or_delim(t_list *redirects, const char *file_or_delim)
{
	if (redirects == NULL)
		return ;
	((t_redirect_info *)(redirects->content))->file_or_delim = file_or_delim;
}
