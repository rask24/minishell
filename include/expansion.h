/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:58:13 by yliu              #+#    #+#             */
/*   Updated: 2024/10/07 15:41:25 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "builtins.h"
# include "libft.h"
# include "env.h"

t_list	*expand(t_list *cmd_args, t_ctx *ctx);

char	*expand_variable(char *str, t_ctx *ctx, bool is_smart_expand);
char	*expand_quotes(char *str);

#endif
