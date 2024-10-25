/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:52:16 by yliu              #+#    #+#             */
/*   Updated: 2024/10/25 19:48:56 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "utils.h"

void	consume_char(t_string *string)
{
	string->left++;
	string->right++;
}

char	*trim(t_string *string)
{
	ptrdiff_t	len;
	char		*result;

	len = (size_t)(string->right - string->left);
	result = ft_xstrndup(string->left, len);
	string->left = string->right;
	return (result);
}

char	*trim_till(t_string *string, const char *set)
{
	while (*string->right && !ft_strchr(set, *string->right))
		string->right++;
	return (trim(string));
}

t_string	*construct_string_struct(char *input)
{
	t_string	*string;

	string = ft_xmalloc(sizeof(t_string));
	string->left = input;
	string->right = input;
	return (string);
}

void	destroy_string_struct(t_string *string)
{
	free(string);
}
