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

static volatile sig_atomic_t	g_caught_signal;

static void	sig_handler(int signum)
{
	(void)signum;
	g_caught_signal = 1;
}

void	cub_signals_install(void)
{
	g_caught_signal = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, SIG_IGN);
}

void	cub_signals_restore(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

int	cub_signal_stop_requested(void)
{
	return (g_caught_signal != 0);
}
