/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/09/27 00:11:51 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "builtins.h"
# include "utils.h"

typedef struct s_expand_info	t_expand_info;

typedef char					*(*t_trim)(t_expand_info *);
typedef void					(*t_discard_char)(t_expand_info *);
typedef void					(*t_find_set)(t_expand_info *, char *);
typedef char					*(*t_trim_till)(t_expand_info *, char *);

typedef struct s_expand_info
{
	char						*left;
	char						*right;
	t_trim						trim;
	t_discard_char				consume_char;
	t_find_set					find_set;
	t_trim_till					trim_till;
}								t_expand_info;

typedef char					*(*t_exec_func)(t_expand_info *,
									t_ctx*);

void							construct_expand_info(char *str,
									t_expand_info *ctx);
char							*expand_variable(char *str,
									t_ctx *ctx);
char							*expand_quotes(char *str, t_ctx *ctx);
char							*get_expanded_variable(t_expand_info *str,
									t_ctx *ctx);

#endif
