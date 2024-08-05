/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_set_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:24:42 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/03 20:16:52 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	increase_eat_cont(t_philo *philo)
{
	if (sem_wait(philo->eat_cont_sem) != 0)
		return ;
	philo->eat_cont++;
	if (sem_post(philo->eat_cont_sem) != 0)
		return ;
}

int	set_philo_status(t_table *table)
{
	sem_wait(table->state);
	table->state_philo = 1;
	sem_post(table->state);
	return (1);
}

void	set_last_eat_time(t_philo *philo, long new_time)
{
	sem_wait(philo->time_since_eat);
	philo->time_from_eat = new_time;
	sem_post(philo->time_since_eat);
}

void	set_finish_dinner(t_philo *philo, int flag)
{
	sem_wait(philo->finish_meal);
	if (flag == 1)
		philo->finished_meal = 1;
	else if (flag == 2)
		philo->finished_meal = 2;
	sem_post(philo->finish_meal);
}
