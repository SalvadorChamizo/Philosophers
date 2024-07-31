/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:52:46 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/31 13:57:00 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

	if (pthread_mutex_lock(&table->init_time) != 0)
		return (0);
	init_time = table->initial_time;
	if (pthread_mutex_unlock(&table->init_time) != 0)
		return (0);
	return (init_time);
}

void	set_initial_time(t_table *table)
{
	if (pthread_mutex_lock(&table->init_time) != 0)
		return ;
	table->initial_time = get_time_milli();
	if (pthread_mutex_unlock(&table->init_time) != 0)
		return ;
}

int	ft_usleep(t_table *table, long sleep_time)
{
	long	sleep_start;
	long	elapsed;

	sleep_start = get_time_micro();
	while (get_time_micro() - sleep_start < sleep_time)
	{
		if (check_finish_dinner(table))
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
