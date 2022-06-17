/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssama <youssama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:07:03 by youssama          #+#    #+#             */
/*   Updated: 2022/06/17 11:21:22 by youssama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (r);
}

unsigned long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + t.tv_usec / 1000);
}

long long	m_time(long long past, long long pres)
{
	return (pres - past);
}

void	my_sleep(long long time, t_philo *philo)
{
	long long	i;

	i = timestamp();
	while (!(philo->dead))
	{
		if (m_time(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	philo_do(t_const_philo *philo, int id, char *str)
{
	sem_wait(philo->var->act);
	if (!(philo->var->dead))
	{
		printf("%lums\t ", timestamp() - philo->var->time_birth);
		printf("philo %i ", id);
		printf("%s\n", str);
	}
	sem_post(philo->var->act);
	return ;
}
