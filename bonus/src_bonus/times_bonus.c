/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:52:46 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/03 18:52:28 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

long	get_time_milli(void)
{
	struct timeval	tv;
	long			seconds_since_unix_epoch;
	long			this_second_milliseconds;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error in gettimeofday()\n");
		return (0);
	}
	seconds_since_unix_epoch = tv.tv_sec * 1000;
	this_second_milliseconds = tv.tv_usec / 1000;
	return (seconds_since_unix_epoch + this_second_milliseconds);
}

long	get_time_micro(void)
{
	struct timeval	tv;
	long			seconds_since_unix_epoch;
	long			this_second_microseconds;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error in gettimeofday()\n");
		return (0);
	}
	seconds_since_unix_epoch = tv.tv_sec * 1000000;
	this_second_microseconds = tv.tv_usec;
	return (seconds_since_unix_epoch + this_second_microseconds);
}

long	check_init_time(t_table *table)
{
	long	init_time;

	if (sem_wait(table->init_time) != 0)
		return (0);
	init_time = table->initial_time;
	if (sem_post(table->init_time) != 0)
		return (0);
	return (init_time);
}

void	set_initial_time(t_table *table)
{
	if (sem_wait(table->init_time) != 0)
		return ;
	table->initial_time = get_time_milli();
	if (sem_wait(table->init_time) != 0)
		return ;
}

int	ft_usleep(t_philo *philo, long sleep_time)
{
	long	sleep_start;
	long	elapsed;

	sleep_start = get_time_micro();
	while (get_time_micro() - sleep_start < sleep_time)
	{
		if (check_finish_dinner(philo))
			return (1);
		elapsed = sleep_time - (get_time_micro() - sleep_start);
		if (elapsed > 1000)
			usleep(500);
		else
		{
			while (get_time_micro() - sleep_start < sleep_time)
				;
		}
	}
	return (0);
}
