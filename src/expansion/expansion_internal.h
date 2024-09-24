/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:09:46 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 13:34:23 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_INTERNAL_H
# define EXPANSION_INTERNAL_H

# include "builtins.h"
# include "utils.h"

void	update_expanded(char **expanded, char *result);
char	*expand_variable(char *string, t_builtins_ctx *ctx);

#endif
