/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/10/07 16:01:45 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "builtins.h"
# include "utils.h"

typedef t_string	t_expand_info;

char				*expand_variable(char *str, t_ctx *ctx,
						bool is_smart_expand);
char				*expand_quotes(char *input);

t_list				*expand_quotes_on_list(t_list *list);
t_list				*expand_variable_on_list(t_list *list, t_ctx *ctx);
t_list				*expand_wildcard_on_list(t_list *list);

bool				wildcard_lazy_match(const char *str, const char *pattern);
char				*trim_expanded_variable(t_expand_info *expand_info,
						t_ctx *ctx);
#endif
