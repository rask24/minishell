/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/10/05 20:14:30 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "builtins.h"
# include "utils.h"

typedef t_string	t_expand_info;

char				*expand_variable(char *str, t_ctx *ctx);
char				*expand_quotes(char *str);
char				*trim_expanded_variable(t_expand_info *expand_info,
						t_ctx *ctx);
#endif
