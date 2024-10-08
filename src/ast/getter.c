/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:25:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/04 23:05:28 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

const char	*get_cmd_arg(t_list *cmd_args)
{
	if (cmd_args == NULL)
		return (NULL);
	return ((const char *)(cmd_args->content));
}

t_redirect_type	get_redirect_type(t_list *redirects)
{
	if (redirects == NULL)
		return (REDIRECT_UNKNOWN);
	return (((t_redirect_info *)(redirects->content))->type);
}

const char	*get_redirect_file_or_delim(t_list *redirects)
{
	if (redirects == NULL)
		return (NULL);
	return (((t_redirect_info *)(redirects->content))->file_or_delim);
}

int	get_heredoc_fd(t_list *redirects)
{
	if (redirects == NULL)
		return (-1);
	return (((t_redirect_info *)(redirects->content))->heredoc_fd);
}
