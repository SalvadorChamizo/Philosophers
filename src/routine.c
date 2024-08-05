/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:34:22 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/05 11:08:59 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	one_philo_case(t_philo *philo)
{
	if (philo->table->philo_num == 1)
	{
		while (!check_finish_dinner(philo->table))
			;
		if (pthread_mutex_unlock(philo->r_fork) != 0)
			return (1);
		return (1);
	}
	return (0);
}

void	increase_eat_cont(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->eat_cont_mutex) != 0)
		return ;
	philo->eat_cont++;
	if (pthread_mutex_unlock(&philo->eat_cont_mutex) != 0)
		return ;
}

void	*ft_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (!check_philo_status(philo->table))
		;
	while (!check_init_time(philo->table))
		;
	if (philo->table->philo_num != 1 && philo->philo_id % 2 == 0)
		ft_usleep(philo->table, 30000);
	set_last_eat_time(philo, check_init_time(philo->table));
	while (!check_finish_dinner(philo->table))
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
	return (NULL);
}
