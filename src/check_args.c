/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:38:08 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/17 14:40:39 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_digits(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_str_isdigit(argv[i]))
		{
			printf("Error in \"%s\": Arguments must be numeric\n", argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_num_philos(int *args)
{
	if (args[0] > 250)
	{
		printf("Error in \"%d\": Too many philosophers\n", args[0]);
		return (0);
	}
	if (args[0] <= 0)
	{
		printf("Error in \"%d\": Not enough philosophers\n", args[0]);
		return (0);
	}
	return (1);
}

int	check_times(int *args)
{
	int	i;

	i = 1;
	while (args[i] && i < 4)
	{
		if (args[i] < 0)
		{
			printf("Error in \"%d\": Times must be positives\n", args[i]);
			return (0);
		}
		printf("%d\n", args[i]);
		i++;
	}
	return (1);
}

int	check_eat_times(int *args)
{
	if (args[4] < 0)
	{
		printf("Error in \"%d\": They have to eat at least 0 times\n", args[4]);
		return (0);
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	*args;
	int	i;

	i = 1;
	args = build_array(argc, argv);
	if (args == 0)
		return (0);
	if (!check_digits(argc, argv))
		return (0);
	if (!check_num_philos(args))
		return (0);
	if (!check_times(args))
		return (0);
	if (argc == 6)
	{
		if (!check_eat_times(args))
			return (0);
	}
	return (1);
}
