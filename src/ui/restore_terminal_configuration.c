/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_terminal_configuration.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:38:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/08/27 00:51:08 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void	restore_terminal_configuration(struct termios *original_termios)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original_termios) == -1)
		perror("tcsetattr");
}
