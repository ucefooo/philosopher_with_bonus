/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssama <youssama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:09:20 by youssama          #+#    #+#             */
/*   Updated: 2022/06/18 22:34:58 by youssama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_const
{
	int					id;
	int					ate;
	int					dead_philo;
	unsigned long		time_last_eat;
	pthread_t			*philo_thread;
	struct s_philo		*var;
}t_const_philo;

typedef struct s_philo
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	int					dead;
	int					*pid;
	unsigned long		time_birth;
	sem_t				*fork;
	sem_t				*act;
	t_const_philo		*var;
}	t_philo;

int				doo(t_philo *philo);
void			destroy_sem(t_philo *philo);
void			*check_death(t_const_philo *philo);
void			process_kill(t_philo *param);
void			create_proc(t_philo *philo, int *pid);
int				init_var(t_philo *philo, char **av);
int				init_sema(t_philo *philo);
void			*philos_process(t_philo *philos, int i);
void			life(t_const_philo *philo);
void			philo_eat(t_const_philo *philo);
void			philo_do(t_const_philo *philo, int id, char *str);
void			my_sleep(long long time, t_philo *data);
long long		m_time(long long past, long long pres);
unsigned long	timestamp(void);
int				ft_atoi(char *str);

#endif