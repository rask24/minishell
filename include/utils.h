/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:27:21 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/06 14:08:40 by yliu             ###   ########.fr       */
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

# define TEMPLATE_LEN 40
# define HEREDOC_PIPESIZE 4096
# define HEREDOC_TMPFILE "minishell-thd"
# define EX_HEREDOC_TMPFILE "ex-minishell-thd"

typedef bool	(*t_pred)(t_list *node, void *param);
typedef void	(*t_del)(void *);
typedef bool	(*t_cmp)(t_list *, t_list *);

bool			is_identifier(const char *input);

int				create_tmpfile(char *tmp_name, size_t tmp_len,
					const char *target);

void			print_error(const char *func, const char *desc);
void			print_error_exit(const char *func, const char *desc,
					int exit_status);
void			print_syntax_error(const char *token_value);
void			print_heredoc_warning(const char *delimiter);

t_list			*ft_xlstnew(void *content);
char			*ft_xstrdup(const char *s);
char			*ft_xstrjoin(const char *s1, const char *s2);
char			*ft_xstrjoin2(char *s1, const char *s2);
char			*ft_xstrndup(const char *s, size_t n);

void			ft_lstremove(t_list **lst, t_list *node, t_del del);
void			ft_lstremove_if(t_list **lst, t_pred should_remove, void *param,
					t_del del);
void			ft_lstreplace(t_list **lst, t_list *node, t_list *new_node);
void			ft_lstinsert(t_list **lst, t_list *insert_ptr, t_list *insert);
void			ft_lstsort(t_list **list, t_cmp cmp);
void			ft_lstiterp(t_list *lst, void (*f)(void *, void *),
					void *param);

typedef struct s_string
{
	char		*left;
	char		*right;
}				t_string;

t_string		*construct_string_struct(char *input);
void			consume_char(t_string *string);
void			destroy_string_struct(t_string *string);
char			*trim(t_string *string);
char			*trim_till(t_string *string, char *set);
#endif
