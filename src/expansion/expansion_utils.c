/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:09:38 by yliu              #+#    #+#             */
/*   Updated: 2024/09/29 13:41:28 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

char	*trim(t_expand_info *expand_info)
{
	ptrdiff_t	len;
	char		*result;

	len = (size_t)(expand_info->right - expand_info->left);
	result = ft_xstrndup(expand_info->left, len);
	expand_info->left = expand_info->right;
	return (result);
}

void	consume_char(t_expand_info *expand_info)
{
	expand_info->left++;
	expand_info->right++;
}

char	*trim_till(t_expand_info *expand_info, char *set)
{
	while (*expand_info->right && !ft_strchr(set, *expand_info->right))
		expand_info->right++;
	return (trim(expand_info));
}

t_expand_info	*construct_expand_info(char *input)
{
	t_expand_info	*expand_info;

	expand_info = ft_xmalloc(sizeof(t_expand_info));
	expand_info->left = input;
	expand_info->right = input;
	return (expand_info);
}

void	destroy_expand_info(t_expand_info *expand_info)
{
	free(expand_info);
	return ;
}
