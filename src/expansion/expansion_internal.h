/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/10/04 23:08:43 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "builtins.h"
# include "utils.h"

typedef struct s_expand_info
{
	char		*left;
	char		*right;
}				t_expand_info;

char			*expand_quotes(char *input);
t_list			*expand_quotes_on_list(t_list *list);
char			*expand_variable(char *str, t_ctx *ctx);
t_list			*expand_variable_on_list(t_list *list, t_ctx *ctx);
t_list			*expand_wildcard_on_list(t_list *list);

char			*trim_expanded_variable(t_expand_info *expand_info, t_ctx *ctx);
bool			wildcard_lazy_match(const char *str, const char *pattern);

t_expand_info	*construct_expand_info(char *input);
void			consume_char(t_expand_info *expand_info);
void			destroy_expand_info(t_expand_info *expand_info);
char			*trim(t_expand_info *expand_info);
char			*trim_till(t_expand_info *expand_info, char *set);

#endif
