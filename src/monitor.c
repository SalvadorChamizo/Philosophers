/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:43:27 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/30 18:55:58 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_philo *philo)
{
	long	last_eat_time;
	long	elapsed;

	last_eat_time = check_last_eat(philo);
	elapsed = (get_time_micro() - last_eat_time) / 1000;
	if (elapsed > philo->table->time_to_die)
	{
		set_finish_dinner(philo->table);
		ft_printing(philo, DIE);
		return (1);
	}
	return (0);
}

int	check_full_philos(t_philo *philo)
{
	int	max_eats;
	int	times_philo_eat;

	max_eats = philo->table->must_eat;
	if (max_eats == -1)
		return (0);
	times_philo_eat = check_if_full(philo);
	if (times_philo_eat >= max_eats)
		return (1);
	return (0);
}

void	*ft_monitor(void *table_dinner)
{
	t_table	*table;
	int		i;
	int		full_cont;

	table = (t_table *)table_dinner;
	set_initial_time(table);
	while (!check_finish_dinner(table))
	{
		i = 0;
		full_cont = 0;
		while (i < table->philo_num)
		{
			if (check_death(&table->philos[i]))
				break ;
			if (check_full_philos(&table->philos[i]))
				full_cont++;
			i++;
		}
		if (full_cont == table->philo_num)
			set_finish_dinner(table);
	}
	return (NULL);
}
