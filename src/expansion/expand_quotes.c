/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:59:47 by yliu              #+#    #+#             */
/*   Updated: 2024/09/28 20:39:12 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static char	*remove_double_quote(t_expand_info *expand_info, t_ctx *ctx)
{
	char	*unquoted;
	char	*result;

	result = NULL;
	while (*expand_info->right && *expand_info->right != '\"')
	{
		if (*expand_info->right == '$')
			unquoted = get_expanded_variable(expand_info, ctx);
		else
			unquoted = expand_info->trim_till(expand_info, "\"$");
		result = ft_xstrjoin2(result, unquoted);
		free(unquoted);
	}
	return (result);
}

static void	deal_with_single(t_expand_info *expand_info, char **unquoted)
{
	expand_info->consume_char(expand_info);
	*unquoted = expand_info->trim_till(expand_info, "\'");
	expand_info->consume_char(expand_info);
}

char	*expand_quotes(char *string, t_ctx *ctx)
{
	t_expand_info	expand_info;
	char			*unquoted;
	char			*expanded;

	construct_expand_info(string, &expand_info);
	expanded = NULL;
	while (*expand_info.right)
	{
		if (*expand_info.right == '\'')
			deal_with_single(&expand_info, &unquoted);
		else if (*expand_info.right == '\"')
		{
			expand_info.consume_char(&expand_info);
			unquoted = remove_double_quote(&expand_info, ctx);
			expand_info.consume_char(&expand_info);
		}
		else
			unquoted = expand_info.trim_till(&expand_info, "\'\"");
		expanded = ft_xstrjoin2(expanded, unquoted);
		free(unquoted);
	}
	return (expanded);
}
