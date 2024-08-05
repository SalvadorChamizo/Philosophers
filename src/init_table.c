/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:10 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/05 12:37:13 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_table_aux(t_table *table, int *args, int argc);

t_table	*init_table(int argc, char **argv)
{
	int		*args;
	t_table	*table;

	args = build_array(argc, argv);
	if (!args)
		return (NULL);
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * args[0]);
	if (!table->forks)
	{
		free(args);
		free(table);
		return (NULL);
	}
	init_table_aux(table, args, argc);
	free(args);
	return (table);
}

void	init_table_aux(t_table *table, int *args, int argc)
{
	table->philos = malloc(sizeof(t_philo) * args[0]);
	if (!table->philos)
	{
		free(args);
		free(table->forks);
		free(table);
		return ;
	}
	table->philo_num = args[0];
	table->time_to_die = args[1];
	table->time_to_eat = args[2];
	table->time_to_sleep = args[3];
	table->must_eat = -1;
	if (argc == 6)
		table->must_eat = args[4];
	table->state_philo = 0;
	table->initial_time = 0;
	table->start_meal = 0;
	table->finished_meal = 0;
	if (!init_mutex(table))
		return ;
	init_philos(table);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	if (!safe_mutex_init(table))
		return (0);
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			i--;
			while (i >= 0)
				pthread_mutex_destroy(&table->forks[i--]);
			pthread_mutex_destroy(&table->write);
			pthread_mutex_destroy(&table->state);
			pthread_mutex_destroy(&table->init_time);
			pthread_mutex_destroy(&table->start);
			pthread_mutex_destroy(&table->finish_meal);
			return (0);
		}
		i++;
	}
	init_philo_mutex(table);
	return (1);
}

void	init_philos(t_table *table)
{
	int		i;
	long	philo_num;

	i = 0;
	philo_num = table->philo_num;
	while (i < table->philo_num)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].l_fork = &table->forks[i];
		table->philos[i].r_fork = &table->forks[(i + 1) % philo_num];
		if (table->philos[i].philo_id % 2 == 0)
		{
			table->philos[i].r_fork = &table->forks[i];
			table->philos[i].l_fork = &table->forks[(i + 1) % philo_num];
		}
		table->philos[i].time_from_eat = 0;
		table->philos[i].eat_cont = 0;
		table->philos[i].table = table;
		i++;
	}
}
