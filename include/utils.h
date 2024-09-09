/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:27:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/09 15:20:09 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

# include "libft.h"

typedef bool	(*t_pred)(t_list *node);

void	print_error(const char *func, const char *desc);
void	print_syntax_error(const char *token_value);

t_list	*ft_xlstnew(void *content);
char	*ft_xstrndup(const char *s, size_t n);
char	*ft_xstrdup(const char *s);

void	ft_lstremove_if(t_list **lst, t_pred is_remove, void (*del)(void *));

#endif
