/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/09/29 11:58:20 by yliu             ###   ########.fr       */
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

typedef char	*(*t_exec_func)(t_expand_info *, t_ctx*);

t_expand_info	*construct_expand_info(char *input);
void			destory_expand_info(t_expand_info *expand_info);
char			*expand_variable(char *str, t_ctx *ctx);
char			*expand_quotes(char *str, t_ctx *ctx);
char			*trim_expanded_variable(t_expand_info *expand_info, t_ctx *ctx);

char			*trim(t_expand_info *expand_info);
void			consume_char(t_expand_info *expand_info);
void			find_set(t_expand_info *expand_info, char *set);
char			*trim_till(t_expand_info *expand_info, char *set);

#endif
