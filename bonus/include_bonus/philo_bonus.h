/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:08:50 by schamizo          #+#    #+#             */
/*   Updated: 2024/08/05 11:17:19 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\033[37m"
# define GREYM		"\x1B[38;5;245m"
# define GREYM2		"\x1B[38;5;250m"
# define BOLD		"\033[1m"
# define RESET		"\x1b[0m"
# define CLEAR		"\033[2J"

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef enum e_action_philo
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_action_philo;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				philo_id;
	int				philo_pid;
	pthread_t		monitor;
	sem_t			*time_since_eat;
	sem_t			*eat_cont_sem;
	sem_t			*finish_meal;
	long			time_from_eat;
	long			eat_cont;
	int				finished_meal;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*state;
	sem_t			*start;
	sem_t			*init_time;
	int				state_philo;
	long			initial_time;
	int				start_meal;
}	t_table;

// free_memory

void	close_semaphores(t_table *table);
void	free_table(t_table *table);

// init_table

t_table	*init_table(int argc, char **argv);
void	init_table_aux(t_table *table, int *args, int argc);
void	init_semaphores(t_table *table);
void	init_philos(t_table *table);

// init_table_aux

void	init_philo_mutex(t_table *table);
int		safe_mutex_init(t_table *table);
int		safe_mutex_init_2(t_table *table);

//start_dinner

int		start_dinner(t_table *table);
void	start_philos(t_table *table);

// routine

int		ft_routine(t_philo *philo);
void	increase_eat_cont(t_philo *philo);
int		one_philo_case(t_philo *philo);

// routine_actions

int		ft_printing(t_philo *philo, t_action_philo action);
int		ft_take_forks(t_philo *philo);
int		ft_eating(t_philo *philo);
int		ft_sleeping(t_philo *philo);
int		ft_thinking(t_philo *philo);

// check_mutexes

int		check_philo_status(t_table *table);
long	check_last_eat(t_philo *philo);
int		check_finish_dinner(t_philo *philo);
int		check_if_full(t_philo *philo);

// set_mutexes
int		set_philo_status(t_table *table);
void	set_finish_dinner(t_philo *philo, int flag);
void	set_last_eat_time(t_philo *philo, long new_time);

//times

long	get_time_milli(void);
long	get_time_micro(void);
long	check_init_time(t_table *table);
void	set_initial_time(t_table *table);
int		ft_usleep(t_philo *philo, long sleep_time);

// monitor

void	*ft_monitor(void *philo);
int		check_death(t_philo *philo);
int		check_full_philos(t_philo *philo);
void	full_finish(t_table *table, int full_philos);

// finish_dinner

void	finish_dinner(t_table *table);

// check_args

int		check_digits(int argc, char **argv);
int		check_num_philos(int *args);
int		check_times(int *args);
int		check_eat_times(int *args);
int		check_args(int argc, char **argv);

// check_args_utils

int		ft_isdigit(int c);
int		ft_str_isdigit(char *str);
int		ft_atoi(char *str);
int		*build_array(int argc, char **argv);

#endif