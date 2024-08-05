/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:58:41 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/03 19:09:01 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	close_semaphores(t_table *table)
{
	int	i;

	sem_close(table->write);
	sem_close(table->state);
	sem_close(table->init_time);
	sem_close(table->start);
	sem_close(table->forks);
	i = 0;
	while (i < table->philo_num)
	{
		sem_close(table->philos[i].eat_cont_sem);
		sem_close(table->philos[i].time_since_eat);
		sem_close(table->philos[i].finish_meal);
		i++;
	}
	sem_unlink("/write");
	sem_unlink("/state");
	sem_unlink("/init_time");
	sem_unlink("/start");
	sem_unlink("/finish_meal");
	sem_unlink("/forks");
	sem_unlink("/eat_cont_sem");
	sem_unlink("/time_since_eat");
}

void	free_table(t_table *table)
{
	free(table->philos);
	free(table);
}
