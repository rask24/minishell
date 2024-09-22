/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:21:33 by yliu              #+#    #+#             */
/*   Updated: 2024/09/22 17:15:24 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions_internal.h"

char	*process_single_quote(t_expansion *expansions)
{
	char	*section;

	expansions->right++;
	expansions->left++;
	while (*expansions->right && *expansions->right != '\'')
		expansions->right++;
	section = ft_xstrndup(expansions->left,
			expansions->right - expansions->left);
	expansions->right++;
	expansions->left = expansions->right;
	return (section);
}
