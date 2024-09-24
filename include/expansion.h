/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:58:13 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 13:34:10 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "builtins.h"
# include "libft.h"
# include "env.h"

t_list	*expand(t_list *cmd_args, t_builtins_ctx *ctx);

#endif
