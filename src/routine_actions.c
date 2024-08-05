/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:32:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/05 16:48:55 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_printing(t_philo *philo, t_action_philo action)
{
	long	time;

	if (pthread_mutex_lock(&philo->table->write) != 0)
		return (0);
	time = get_time_milli() - check_init_time(philo->table);
	if (check_finish_dinner(philo->table) && action != DIE)
	{
		if (pthread_mutex_unlock(&philo->table->write) != 0)
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
	if (pthread_mutex_unlock(&philo->table->write) != 0)
		return (0);
	return (1);
}

int	ft_take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (1);
	if (check_finish_dinner(philo->table) || !ft_printing(philo, FORK))
	{
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (1);
		return (1);
	}
	if (one_philo_case(philo))
		return (1);
	if (pthread_mutex_lock(philo->l_fork) != 0)
	{
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (1);
		return (1);
	}
	if (check_finish_dinner(philo->table) || !ft_printing(philo, FORK))
	{
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->l_fork) != 0)
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
	if (check_finish_dinner(philo->table) || !ft_printing(philo, EAT))
	{
		if (pthread_mutex_unlock(philo->l_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (1);
		return (1);
	}
	if (philo->table->must_eat != -1)
		increase_eat_cont(philo);
	ft_usleep(philo->table, philo->table->time_to_eat * 1000);
	return (0);
}

int	ft_sleeping(t_philo *philo)
{
	if (check_finish_dinner(philo->table) || !ft_printing(philo, SLEEP))
	{
		if (pthread_mutex_unlock(philo->l_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (1);
		return (1);
	}
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (1);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (1);
	if (ft_usleep(philo->table, philo->table->time_to_sleep * 1000))
		return (1);
	return (0);
}

int	ft_thinking(t_philo *philo)
{
	long	time_to_think;

	if (check_finish_dinner(philo->table) || !ft_printing(philo, THINK))
		return (1);
	if (philo->table->philo_num % 2 == 0)
		return (0);
	time_to_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	if (ft_usleep(philo->table, time_to_think * 1000 / 2))
		return (1);
	return (0);
}
