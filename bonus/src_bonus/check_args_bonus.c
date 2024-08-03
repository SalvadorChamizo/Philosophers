/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:38:08 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/01 14:40:45 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	check_digits(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	while (i < argc)
	{
		if (!ft_str_isdigit(argv[i]))
		{
			printf(RED"Error in "RESET"\"%s\""RED": "RESET"", argv[i]);
			printf("Arguments must be numeric\n");
			flag = 0;
		}
		i++;
	}
	return (flag);
}

int	check_num_philos(int *args)
{
	if (args[0] > 250)
	{
		printf(RED"Error in "RESET"\"%d\""RED": "RESET"", args[0]);
		printf("Too many philosophers\n");
		return (0);
	}
	if (args[0] <= 0)
	{
		printf(RED"Error in "RESET"\"%d\""RED": "RESET"", args[0]);
		printf("Not enough philosophers\n");
		return (0);
	}
	return (1);
}

int	check_times(int *args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	while (i < 4)
	{
		if (args[i] < 0)
		{
			printf(RED"Error in "RESET"\"%d\""RED": "RESET"", args[i]);
			printf("Not enough philosophers\n");
			flag = 0;
		}
		i++;
	}
	return (flag);
}

int	check_eat_times(int *args)
{
	if (args[4] < 0)
	{
		printf(RED"Error in "RESET"\"%d\""RED": "RESET"", args[4]);
		printf("They have to eat at least 0 times\n");
		return (0);
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	*args;
	int	i;
	int	flag;

	args = NULL;
	i = 1;
	flag = 1;
	args = build_array(argc, argv);
	if (args == NULL)
		return (0);
	if (!check_digits(argc, argv))
		flag = 0;
	if (!check_num_philos(args))
		flag = 0;
	if (!check_times(args))
		flag = 0;
	if (argc == 6)
	{
		if (!check_eat_times(args))
			flag = 0;
	}
	free(args);
	return (flag);
}
