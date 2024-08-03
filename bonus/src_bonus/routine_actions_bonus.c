/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:32:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/03 20:12:53 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	ft_printing(t_philo *philo, t_action_philo action)
{
	long	time;

	if (sem_wait(philo->table->write) != 0)
		return (0);
	time = get_time_milli() - philo->table->initial_time;
	if (check_finish_dinner(philo) && action != DIE)
	{
		if (sem_post(philo->table->write) != 0)
			return (0);
		return (0);
	}
	if (action == FORK)
		printf("%ld %d %s\n", time, philo->philo_id, TAKE_FORKS);
	if (action == EAT)
		printf("%ld %d %s\n", time, philo->philo_id, EATING);
	if (action == SLEEP)
		printf("%ld %d %s\n", time, philo->philo_id, SLEEPING);
	if (action == THINK)
		printf("%ld %d %s\n", time, philo->philo_id, THINKING);
	if (action == DIE)
		printf("%ld %d %s\n", time, philo->philo_id, DIED);
	if (sem_post(philo->table->write) != 0)
		return (0);
	return (1);
}

int	ft_take_forks(t_philo *philo)
{
	if (sem_wait(philo->table->forks) != 0)
		return (1);
	if (check_finish_dinner(philo) || !ft_printing(philo, FORK))
	{
		if (sem_post(philo->table->forks) != 0)
			return (1);
		return (1);
	}
	if (one_philo_case(philo))
		return (1);
	if (sem_wait(philo->table->forks) != 0)
	{
		if (sem_post(philo->table->forks) != 0)
			return (1);
		return (1);
	}
	if (check_finish_dinner(philo) || !ft_printing(philo, FORK))
	{
		if (sem_post(philo->table->forks) != 0)
			return (1);
		if (sem_post(philo->table->forks) != 0)
			return (1);
		return (1);
	}
	return (0);
}

int	ft_eating(t_philo *philo)
{
	long	new_time;

	new_time = get_time_milli();
	set_last_eat_time(philo, new_time);
	if (check_finish_dinner(philo) || !ft_printing(philo, EAT))
	{
		if (sem_post(philo->table->forks) != 0)
			return (1);
		if (sem_post(philo->table->forks) != 0)
			return (1);
		return (1);
	}
	ft_usleep(philo, philo->table->time_to_eat * 1000);
	return (0);
}

int	ft_sleeping(t_philo *philo)
{
	if (!ft_printing(philo, SLEEP))
		return (1);
	if (sem_post(philo->table->forks) != 0)
		return (1);
	if (sem_post(philo->table->forks) != 0)
		return (1);
	increase_eat_cont(philo);
	if (ft_usleep(philo, philo->table->time_to_sleep * 1000))
		return (1);
	return (0);
}

int	ft_thinking(t_philo *philo)
{
	long	time_to_think;

	if (check_finish_dinner(philo) || !ft_printing(philo, THINK))
		return (1);
	if (philo->table->philo_num % 2 == 0)
		return (0);
	time_to_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	if (ft_usleep(philo, time_to_think * 1000 / 2))
		return (1);
	return (0);
}
