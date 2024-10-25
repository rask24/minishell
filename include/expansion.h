/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:58:13 by yliu              #+#    #+#             */
/*   Updated: 2024/10/25 19:47:12 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "ctx.h"
# include "libft.h"

t_list	*expand(t_list *cmd_args, t_ctx *ctx);

char	*expand_variable_heredoc(char *str, t_ctx *ctx);
char	*expand_quotes(char *str);

#endif
