/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssama <youssama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:55 by youssama          #+#    #+#             */
/*   Updated: 2022/05/25 00:08:06 by youssama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, unsigned long time, char *is_doing)
{
	pthread_mutex_lock(philo->print);
	printf("%lums	%d %s\n", time, philo->id, is_doing);
	pthread_mutex_unlock(philo->print);
}

void	*doo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->last_meal = in_time();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->id - 1]);
		print(philo, real_time(philo), "has taken a fork");
		pthread_mutex_lock(&philo->mutex[philo->id % philo->var->num_philo]);
		print(philo, real_time(philo), "has taken a fork");
		print(philo, real_time(philo), "is eating");
		philo->ate++;
		if (philo->ate == philo->var->must_eat)
			philo->var->total_ate++;
		usleep(philo->var->time_eat * 1000);
		philo->last_meal = in_time();
		pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->id % philo->var->num_philo]);
		print(philo, real_time(philo), "is sleeping");
		usleep(philo->var->time_sleep * 1000);
		print(philo, real_time(philo), "is thinking");
	}
	return (0);
}

void	func(t_philo *philo, t_const_philo *var)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].var->total_ate == philo[i].var->num_philo)
		{
			dest_mutex(philo);
			free_param(philo, philo->mutex, var);
			return ;
		}
		if (in_time() - philo[i].last_meal
			> (unsigned long)var->time_die)
		{
			usleep(100);
			pthread_mutex_lock(philo->print);
			printf("%lums	%d died", real_time(philo), philo->id);
			dest_mutex(philo);
			free_param(philo, philo->mutex, var);
			return ;
		}
		i = (i + 1) % var->num_philo;
		usleep(500);
	}
}

int	exit_error(void)
{
	printf("Error in Params please enter: num_philo\
	time_die time_eat time_sleep (num_eat)\n");
	return (1);
}

int	main(int c, char **v)
{
	int				i;
	t_const_philo	*var;
	t_philo			*philo;
	pthread_t		*th;

	if (c < 5 || c > 6)
		return (exit_error());
	var = (t_const_philo *)malloc(sizeof(t_const_philo));
	if (arg_to_param(var, v))
		return (free_param(0, 0, var));
	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_philo);
	if (init_param(philo, var))
		return (1);
	th = (pthread_t *)malloc(sizeof(pthread_t) * var->num_philo);
	i = -1;
	while (++i < philo->var->num_philo)
	{
		pthread_create(&th[i], NULL, doo, philo + i);
		usleep(100);
	}
	func(philo, var);
	free(th);
	return (0);
}
