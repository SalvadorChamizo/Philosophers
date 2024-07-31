/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:35:14 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/30 18:56:38 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_wait_monitor(t_table *table)
{
	int	ret;

	ret = pthread_join(table->monitor, NULL);
	if (ret != 0)
		printf("Error in pthread_join\n");
}

void	ft_wait_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_join(table->philos[i].philo, NULL);
		i++;
	}
}

void	finish_dinner(t_table *table)
{
	ft_wait_monitor(table);
	ft_wait_philos(table);
}
