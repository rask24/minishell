/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:27:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/22 23:33:21 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <errno.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "libft.h"

typedef bool	(*t_pred)(t_list *node, void *param);
typedef void	(*t_del)(void *);
typedef bool	(*t_cmp)(t_list *, t_list *);

# define CMD_NOT_FOUND "command not found"

bool			is_identifier(const char *input);

void			print_error(const char *func, const char *desc);
void			print_error_exit(const char *func, const char *desc,
					int exit_status);
void			print_syntax_error(const char *token_value);

t_list			*ft_xlstnew(void *content);
char			*ft_xstrdup(const char *s);
char			*ft_xstrjoin(const char *s1, const char *s2);
char			*ft_xstrndup(const char *s, size_t n);

void			ft_lstremove_if(t_list **lst, t_pred should_remove, void *param,
					t_del del);
void			ft_lstsort(t_list **list, bool (*cmp)(t_list *, t_list *));
void			ft_lstiterp(t_list *lst, void (*f)(void *, void *),
					void *param);

#endif
