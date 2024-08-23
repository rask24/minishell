/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_terminal_configuration.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:34:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/08/23 21:36:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

void	save_terminal_configuration(struct termios *original_termios)
{
	tcgetattr(STDIN_FILENO, original_termios);
}
