/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssama <youssama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 01:11:58 by youssama          #+#    #+#             */
/*   Updated: 2022/05/25 00:04:01 by youssama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_all
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
}t_const_philo;

typedef struct s_philo
{
	int				ate;
	int				id;
	t_const_philo	*var;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	unsigned long	last_meal;
}t_philo;

int				ft_atoi(char *str);
int				exit_error(void);
int				check_arg(char **v);
int				arg_to_param(t_const_philo *var, char **v);
void			assign_param(t_philo *philo, t_const_philo *var,
					pthread_mutex_t *m, pthread_mutex_t *pr);
int				free_param(t_philo *philo, pthread_mutex_t *m,
					t_const_philo *var);
int				init_param(t_philo *philo, t_const_philo *var);
void			dest_mutex(t_philo *philo);
unsigned long	in_time(void);
unsigned long	real_time(t_philo *philo);
void			print(t_philo *philo, unsigned long time, char *is_doing);
void			*doo(void *p);
void			func(t_philo *philo, t_const_philo *var);

#endif