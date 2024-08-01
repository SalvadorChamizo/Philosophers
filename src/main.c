/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:40:31 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/31 18:32:54 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			return (1);
		table = init_table(argc, argv);
		if (!table)
			return (1);
		start_dinner(table);
		finish_dinner(table);
		destroy_mutex(table);
		free_table(table);
	}
	else
	{
		printf(RED"Error:"RESET" Incorrect number of arguments\n");
		return (1);
	}
	return (0);
}
