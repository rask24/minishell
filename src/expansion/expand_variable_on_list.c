/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_on_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:37:49 by yliu              #+#    #+#             */
/*   Updated: 2024/10/02 14:58:22 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

static bool	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static char	*get_next_ifs_splitted_word(char **input)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (**input == '\0')
		return (NULL);
	while (is_ifs(**input))
		(*input)++;
	while (!is_ifs((*input)[i]) && (*input)[i] != '\0')
		i++;
	result = ft_xstrndup(*input, i);
	*input += i;
	return (result);
}

t_list	*expand_variable_on_list(t_list *list, t_ctx *ctx)
{
	t_list	*curr;
	char	*ifs_combined_word;
	char	*ifs_splitted_word;
	t_list	*result;

	curr = list;
	result = NULL;
	while (curr)
	{
		ifs_combined_word = expand_variable(curr->content, ctx);
		while (true)
		{
			ifs_splitted_word = get_next_ifs_splitted_word(&ifs_combined_word);
			if (ifs_splitted_word == NULL)
				break ;
			ft_lstadd_back(&result, ft_xlstnew(ifs_splitted_word));
		}
		curr = curr->next;
	}
	ft_lstclear(&list, free);
	return (result);
}
