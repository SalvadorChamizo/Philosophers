/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:38:06 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/01 14:40:51 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_str_isdigit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		flag = 1;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (flag);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] && str[i] <= 9 && str[i] >= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			nb = nb * 10 + str[i] - '0';
		else
			return (nb * sign);
		i++;
	}
	return (nb * sign);
}

int	*build_array(int argc, char **argv)
{
	int	*args;
	int	i;
	int	j;

	i = 1;
	j = 0;
	args = malloc(sizeof(int *) * (argc - 1));
	if (!args)
		return (0);
	while (j < argc)
		args[j++] = 0;
	j = 0;
	while (i < argc)
	{
		args[j] = ft_atoi(argv[i]);
		i++;
		j++;
	}
	return (args);
}
