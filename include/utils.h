/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:27:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/11 14:46:40 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

# include "libft.h"
# include "stdlib.h"

typedef bool	(*t_cmp)(t_list *, t_list *);
typedef void	(*t_del)(void *);
typedef bool	(*t_pred)(t_list *node, void *param);

void			print_error(const char *func, const char *desc);

t_list			*ft_xlstnew(void *content);
char			*ft_xstrndup(const char *s, size_t n);
char			*ft_xstrdup(const char *s);

void			ft_lstremove_if(t_list **lst, t_pred is_remove, void *param,
					t_del del);
void			ft_lstsort(t_list **list, t_cmp cmp);

#endif
