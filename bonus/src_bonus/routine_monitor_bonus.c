/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:34:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/05 16:45:37 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	one_philo_case(t_philo *philo)
{
	if (philo->table->philo_num == 1)
	{
		while (check_finish_dinner(philo) == 0)
			;
		if (sem_post(philo->table->forks) != 0)
			return (1);
		return (1);
	}
	return (0);
}

void	one_philo_monitor(t_philo *philo)
{
	long	time;

	if (philo->table->philo_num == 1)
	{
		ft_usleep(philo, (philo->table->time_to_die * 0.95) * 1000);
		set_finish_dinner(philo, 1);
		sem_wait(philo->table->write);
		time = philo->table->time_to_die + 1;
		printf("%ld %d %s\n", time, philo->philo_id, DIED);
		exit (1);
	}
}

void	check_for_death(t_philo *philo)
{
	long	time;

	time = get_time_milli() - philo->table->initial_time;
	set_finish_dinner(philo, 1);
	sem_wait(philo->table->write);
	printf("%ld %d %s\n", time, philo->philo_id, DIED);
	close_semaphores(philo->table);
	free_table(philo->table);
	exit (1);
}

void	*ft_monitor(void *philosopher)
{
	t_philo	*philo;
	long	time_die;
	int		max_eat;

	philo = (t_philo *)philosopher;
	time_die = philo->table->time_to_die;
	max_eat = philo->table->must_eat;
	one_philo_monitor(philo);
	while (check_finish_dinner(philo) == 0)
	{
		if ((get_time_milli() - check_last_eat(philo)) > time_die)
			check_for_death(philo);
		if (max_eat != -1 && max_eat <= check_if_full(philo))
		{
			set_finish_dinner(philo, 2);
			break ;
		}
	}
	return (NULL);
}

int	ft_routine(t_philo *philo)
{
	philo->table->initial_time = get_time_milli();
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo, 30000);
	philo->time_from_eat = philo->table->initial_time;
	pthread_create(&philo->monitor, NULL, &ft_monitor, philo);
	pthread_detach(philo->monitor);
	while (check_finish_dinner(philo) == 0)
	{
		if (ft_take_forks(philo))
			break ;
		if (ft_eating(philo))
			break ;
		if (ft_sleeping(philo))
			break ;
		if (ft_thinking(philo))
			break ;
	}
	close_semaphores(philo->table);
	free_table(philo->table);
	exit (0);
}
