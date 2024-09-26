/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:09:38 by yliu              #+#    #+#             */
/*   Updated: 2024/09/26 18:35:35 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static char	*trim(t_expand_info *expand_info)
{
	ptrdiff_t	len;
	char		*result;

	len = (size_t)(expand_info->right - expand_info->left);
	result = ft_xstrndup(expand_info->left, len);
	expand_info->left = expand_info->right;
	return (result);
}

static void	consume_char(t_expand_info *expand_info)
{
	expand_info->left++;
	expand_info->right++;
}

static void	find_set(t_expand_info *expand_info, char *set)
{
	while (*expand_info->right && !ft_strchr(set, *expand_info->right))
		expand_info->right++;
}

static char	*trim_till(t_expand_info *expand_info, char *set)
{
	expand_info->find_set(expand_info, set);
	return (expand_info->trim(expand_info));
}

void	construct_expand_info(char *input, t_expand_info *expand_info)
{
	expand_info->left = input;
	expand_info->right = input;
	expand_info->trim = trim;
	expand_info->consume_char = consume_char;
	expand_info->find_set = find_set;
	expand_info->trim_till = trim_till;
	return ;
}
