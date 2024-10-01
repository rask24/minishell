/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/10/01 13:33:36 by reasuke          ###   ########.fr       */
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

t_expand_info	*construct_expand_info(char *input);
void			destroy_expand_info(t_expand_info *expand_info);
char			*trim_expanded_variable(t_expand_info *expand_info, t_ctx *ctx);

char			*trim(t_expand_info *expand_info);
void			consume_char(t_expand_info *expand_info);
char			*trim_till(t_expand_info *expand_info, char *set);

#endif
