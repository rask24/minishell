/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_ifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:52:40 by yliu              #+#    #+#             */
/*   Updated: 2024/10/31 23:34:57 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static void	proceed_single_quote(t_string *str_info)
{
	str_info->right++;
	while (*str_info->right != '\0' && *str_info->right != '\'')
		str_info->right++;
	return ;
}

static t_list	*extract_none_var_segment(t_string *str_info, bool *is_quoted)
{
	while (!(*str_info->right == '$' || *str_info->right == '\0'))
	{
		if (*str_info->right == '\'' && !*is_quoted)
			proceed_single_quote(str_info);
		else
			if (*str_info->right == '\"')
				*is_quoted = !*is_quoted;
		str_info->right++;
	}
	return (ft_xlstnew(trim(str_info)));
}

static t_list	*split_expanded_variable_by_ifs(char *expanded)
{
	t_expand_info	*expanded_info;
	t_list			*list;

	list = NULL;
	expanded_info = construct_string_struct(expanded);
	while (*expanded_info->right != '\0')
	{
		while (*expanded_info->right != '\0' && !is_ifs(*expanded_info->right))
			expanded_info->right++;
		ft_lstadd_back(&list, ft_xlstnew(trim(expanded_info)));
		if (*expanded_info->right == '\0')
			break ;
		while (*expanded_info->right != '\0' && is_ifs(*expanded_info->right))
			consume_char(expanded_info);
		if (*expanded_info->right == '\0')
			ft_lstadd_back(&list, ft_xlstnew(ft_xstrdup("")));
	}
	destroy_string_struct(expanded_info);
	return (list);
}

t_list	*extract_var_segment(char *expanded_var, bool is_quoted)
{
	t_list	*list;

	list = NULL;
	ft_lstadd_back(&list, ft_xlstnew(NULL));
	if (is_quoted)
		ft_lstadd_back(&list, ft_xlstnew(ft_xstrdup(expanded_var)));
	else
		ft_lstadd_back(&list, split_expanded_variable_by_ifs(expanded_var));
	ft_lstadd_back(&list, ft_xlstnew(NULL));
	return (list);
}

t_list	*split_by_ifs(t_expand_info *expand_info, t_ctx *ctx)
{
	t_list	*list;
	bool	is_quoted;
	char	*expanded_var;
	t_list	*segment;
	t_list	*normed_list;

	list = NULL;
	is_quoted = false;
	while (*expand_info->right != '\0')
	{
		if (*expand_info->right == '$')
		{
			expanded_var = trim_expanded_variable(expand_info, ctx);
			segment = extract_var_segment(expanded_var, is_quoted);
			free(expanded_var);
		}
		else
			segment = extract_none_var_segment(expand_info, &is_quoted);
		ft_lstadd_back(&list, segment);
	}
	normed_list = normalize_list(list);
	ft_lstclear(&list, free);
	return (normed_list);
}
