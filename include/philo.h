/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:08:50 by schamizo          #+#    #+#             */
/*   Updated: 2024/07/17 14:42:26 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

// check_args

int	check_digits(int argc, char **argv);
int	check_num_philos(int *args);
int	check_times(int *args);
int	check_eat_times(int *args);
int	check_args(int argc, char **argv);

// check_args_utils

int	ft_isdigit(int c);
int	ft_str_isdigit(char *str);
int	ft_atoi(char *str);
int	*build_array(int argc, char **argv);

#endif