/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/10/25 19:55:31 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "ctx.h"
# include "libft.h"

typedef t_string	t_expand_info;

char				*expand_variable_heredoc(char *str, t_ctx *ctx);
char				*expand_quotes(char *input);

t_list				*expand_quotes_on_list(t_list *list);
t_list				*expand_variable_on_list(t_list *list, t_ctx *ctx);
t_list				*expand_wildcard_on_list(t_list *list);

t_list				*normalize_list(t_list *curr);
t_list				*split_by_ifs(t_expand_info *expand_info, t_ctx *ctx);

bool				wildcard_lazy_match(const char *str, const char *pattern);

char				*trim_expanded_variable(t_expand_info *expand_info,
						t_ctx *ctx);
#endif
