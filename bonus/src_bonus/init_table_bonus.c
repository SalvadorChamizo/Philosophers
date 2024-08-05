/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:10 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/05 17:12:35 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

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
	{
		free(args);
		return (NULL);
	}
	table->philos = malloc(sizeof(t_philo) * args[0]);
	if (!table->philos)
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
	init_philos(table);
	init_semaphores(table);
}

void	init_philos(t_table *table)
{
	int		i;
	long	philo_num;

	i = 0;
	sem_unlink("/finish_meal");
	sem_unlink("/time_since_eat");
	sem_unlink("/eat_cont_sem");
	philo_num = table->philo_num;
	while (i < table->philo_num)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].time_from_eat = 0;
		table->philos[i].eat_cont = 0;
		table->philos[i].finished_meal = 0;
		table->philos[i].table = table;
		table->philos[i].time_since_eat \
		= sem_open("/time_since_eat", O_CREAT, 0700, 1);
		table->philos[i].eat_cont_sem \
		= sem_open("/eat_cont_sem", O_CREAT, 0700, 1);
		table->philos[i].finish_meal \
		= sem_open("/time_since_eat", O_CREAT, 0700, 1);
		i++;
	}
}

void	init_semaphores(t_table *table)
{
	sem_unlink("/write");
	sem_unlink("/state");
	sem_unlink("/init_time");
	sem_unlink("/start");
	sem_unlink("/finish_meal");
	sem_unlink("/forks");
	table->write = sem_open("/write", O_CREAT, 0700, 1);
	table->state = sem_open("/state", O_CREAT, 0700, 0);
	table->init_time = sem_open("/init_time", O_CREAT, 0700, 1);
	table->start = sem_open("/start", O_CREAT, 0700, 1);
	table->forks = sem_open("/forks", O_CREAT, 0700, table->philo_num);
	if (table->write == 0 || table->state == 0 || table->init_time == 0
		|| table->start == 0)
		return ;
	if (table->forks == 0)
		return ;
}
