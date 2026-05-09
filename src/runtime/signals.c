/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kebris-c <kebris-c@student.42madrid.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 00:00:00 by kebris-c        #+#    #+#               */
/*   Updated: 2026/04/22 00:00:00 by kebris-c       ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <signal.h>

/**
 * @brief Function that returns a pointer to the exit flag.
 * 
 * This function returns a pointer to the exit flag. This is used to
 * store the exit flag in a static variable.
 * 
 * @return A pointer to the exit flag.
 *
 * You can avoid globals by using a pointer to a static variable.
 */

static volatile sig_atomic_t	*signals_exit_flag_storage(void)
{
	static volatile sig_atomic_t	v;

	return (&v);
}

static void	sig_handler(int signum)
{
	(void)signum;
	*signals_exit_flag_storage() = 1;
}

void	signals_install(void)
{
	*signals_exit_flag_storage() = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_restore(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

int	signals_exit_was_requested(void)
{
	return (*signals_exit_flag_storage() != 0);
}
