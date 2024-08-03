/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:22:24 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/03 18:49:06 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	check_philo_status(t_table *table)
{
	int	philo_status;

	sem_wait(table->state);
	philo_status = table->state_philo;
	sem_post(table->state);
	return (philo_status);
}

long	check_last_eat(t_philo *philo)
{
	long	last_eat_time;

	sem_wait(philo->time_since_eat);
	last_eat_time = philo->time_from_eat;
	sem_post(philo->time_since_eat);
	return (last_eat_time);
}

int	check_finish_dinner(t_philo *philo)
{
	int	finish_dinner;

	sem_wait(philo->finish_meal);
	finish_dinner = philo->finished_meal;
	sem_post(philo->finish_meal);
	return (finish_dinner);
}

int	check_if_full(t_philo *philo)
{
	int	times_eaten;

	sem_wait(philo->eat_cont_sem);
	times_eaten = philo->eat_cont;
	sem_post(philo->eat_cont_sem);
	return (times_eaten);
}
