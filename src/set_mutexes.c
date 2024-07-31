/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mutexes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:24:42 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/31 12:25:25 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	set_philo_status(t_table *table)
{
	if (pthread_mutex_lock(&table->state) != 0)
		return (0);
	table->state_philo = 1;
	if (pthread_mutex_unlock(&table->state) != 0)
		return (0);
	return (1);
}

void	set_last_eat_time(t_philo *philo, long new_time)
{
	if (pthread_mutex_lock(&philo->time_since_eat) != 0)
		return ;
	philo->time_from_eat = new_time;
	if (pthread_mutex_lock(&philo->time_since_eat) != 0)
		return ;
}

void	set_finish_dinner(t_table *table)
{
	if (pthread_mutex_lock(&table->finish_meal) != 0)
		return ;
	table->finished_meal = 1;
	if (pthread_mutex_unlock(&table->finish_meal) != 0)
		return ;
}
