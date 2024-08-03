/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:26:11 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/03 20:12:39 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

void	start_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].philo_pid = fork();
		if (table->philos[i].philo_pid < 0)
		{
			printf("Error: Failed to create philo fork\n");
			return ;
		}
		if (table->philos[i].philo_pid == 0)
		{
			ft_routine(&table->philos[i]);
			exit(0);
		}
		i++;
	}
}

int	start_dinner(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	start_philos(table);
	while (i < table->philo_num)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			while (i < table->philo_num)
			{
				kill(table->philos[i].philo_pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	if (status == 0)
		printf(GREEN"All philos are full\n"RESET);
	return (0);
}
