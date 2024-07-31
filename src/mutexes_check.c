/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:22:24 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/31 13:58:59 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_philo_status(t_table *table)
{
	int	philo_status;

	if (pthread_mutex_lock(&table->state) != 0)
		return (0);
	philo_status = table->state_philo;
	if (pthread_mutex_unlock(&table->state) != 0)
		return (0);
	return (philo_status);
}

long	check_last_eat(t_philo *philo)
{
	long	last_eat_time;

	if (pthread_mutex_lock(&philo->time_since_eat) != 0)
		return (0);
	last_eat_time = philo->time_from_eat;
	if (pthread_mutex_unlock(&philo->time_since_eat) != 0)
		return (0);
	return (last_eat_time);
}

int	check_finish_dinner(t_table *table)
{
	int	finish_dinner;

	if (pthread_mutex_lock(&table->finish_meal) != 0)
		return (0);
	finish_dinner = table->finished_meal;
	if (pthread_mutex_unlock(&table->finish_meal) != 0)
		return (0);
	return (finish_dinner);
}

int	check_if_full(t_philo *philo)
{
	int	times_eaten;

	if (pthread_mutex_lock(&philo->eat_cont_mutex) != 0)
		return (0);
	times_eaten = philo->eat_cont;
	if (pthread_mutex_unlock(&philo->eat_cont_mutex) != 0)
		return (0);
	return (times_eaten);
}
