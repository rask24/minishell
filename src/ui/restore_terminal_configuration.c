/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_terminal_configuration.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:38:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/08/23 21:39:38 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

void	restore_terminal_configuration(struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_termios);
}
