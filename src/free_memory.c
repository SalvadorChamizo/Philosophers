/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:58:41 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/31 11:45:28 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->state);
	pthread_mutex_destroy(&table->init_time);
	pthread_mutex_destroy(&table->start);
	pthread_mutex_destroy(&table->finish_meal);
	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].eat_cont_mutex);
		pthread_mutex_destroy(&table->philos[i].time_since_eat);
		i++;
	}
}
