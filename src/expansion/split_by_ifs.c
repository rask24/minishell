/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_ifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:52:40 by yliu              #+#    #+#             */
/*   Updated: 2024/10/13 00:58:05 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static void	proceed_single_quote(t_string *str_)
{
	str_->right++;
	while (*str_->right != '\0' && *str_->right != '\'')
		str_->right++;
	str_->right++;
	return ;
}

static char	*trim_till_dollar(t_string *str_)
{
	while (!(*str_->right == '$' || *str_->right == '\0'))
	{
		if (*str_->right == '\'')
			proceed_single_quote(str_);
		else
			str_->right++;
	}
	return (trim(str_));
}

static bool	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_list	*split_expanded_variable_by_ifs(char *expanded)
{
	t_string	*expanded_;
	t_list		*list;

	list = NULL;
	expanded_ = construct_string_struct(expanded);
	while (*expanded_->right != '\0')
	{
		while (*expanded_->right != '\0' && !is_ifs(*expanded_->right))
			expanded_->right++;
		ft_lstadd_back(&list, ft_xlstnew(trim(expanded_)));
		if (*expanded_->right == '\0')
			break ;
		while (*expanded_->right != '\0' && is_ifs(*expanded_->right))
			consume_char(expanded_);
		if (*expanded_->right == '\0')
			ft_lstadd_back(&list, ft_xlstnew(ft_xstrdup("")));
	}
	destroy_string_struct(expanded_);
	return (list);
}

t_list	*split_by_ifs(t_string *token_content_, t_ctx *ctx)
{
	t_list	*list;
	char	*tmp;
	t_list	*normed_list;

	list = NULL;
	while (*token_content_->right != '\0')
	{
		if (*token_content_->right == '$')
		{
			ft_lstadd_back(&list, ft_xlstnew(NULL));
			tmp = trim_expanded_variable(token_content_, ctx);
			ft_lstadd_back(&list, split_expanded_variable_by_ifs(tmp));
			ft_lstadd_back(&list, ft_xlstnew(NULL));
		}
		else
		{
			tmp = trim_till_dollar(token_content_);
			ft_lstadd_back(&list, ft_xlstnew(tmp));
		}
	}
	normed_list = normalize_list(list);
	ft_lstclear(&list, free);
	return (normed_list);
}
