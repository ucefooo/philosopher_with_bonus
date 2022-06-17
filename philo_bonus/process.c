/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssama <youssama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:01:41 by youssama          #+#    #+#             */
/*   Updated: 2022/06/17 11:35:57 by youssama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_proc(t_philo *philo, int *pid)
{
	int	i;

	i = 0;
	while (i < philo->nb_philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			philos_process(philo, i);
		i++;
	}
}

void	process_kill(t_philo *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philos)
	{
		kill(param->pid[i], SIGINT);
		i++;
	}
}

void	*check_death(t_const_philo *philo)
{
	unsigned long	now;

	while (1)
	{
		now = timestamp();
		if (philo->ate == philo->var->nb_must_eat)
			return (NULL);
		if (now - philo->time_last_eat >= \
				(unsigned long long)philo->var->time_to_die)
		{
			philo->dead_philo = 1;
			sem_wait(philo->var->act);
			printf("%lums\t philo %d died\n",
				now - philo->var->time_birth, philo->id);
			process_kill(philo->var);
			destroy_sem(philo->var);
			free(philo->var->pid);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}
