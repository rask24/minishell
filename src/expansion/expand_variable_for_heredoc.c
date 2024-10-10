/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_for_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:08:50 by yliu              #+#    #+#             */
/*   Updated: 2024/10/12 23:27:41 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_internal.h"

char	*expand_variable_for_heredoc(char *input, t_ctx *ctx)
{
	t_expand_info	*expand_info;
	char			*trimmed;
	char			*expanded;

	expand_info = construct_string_struct(input);
	expanded = NULL;
	while (*expand_info->right)
	{
		if (*expand_info->right == '$')
			trimmed = trim_expanded_variable(expand_info, ctx);
		else
			trimmed = trim_till(expand_info, "$");
		expanded = ft_xstrjoin2(expanded, trimmed);
		free(trimmed);
	}
	destroy_string_struct(expand_info);
	return (expanded);
}
