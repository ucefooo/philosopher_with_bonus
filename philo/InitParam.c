/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitParam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssama <youssama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:51:59 by youssama          #+#    #+#             */
/*   Updated: 2022/05/25 00:03:23 by youssama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **v)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (v[i])
	{
		j = 0;
		while (v[i][j])
		{
			if ((v[i][j] < '0' || v[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	arg_to_param(t_const_philo *var, char **v)
{
	if (check_arg(v))
		return (exit_error());
	var->total_ate = 0;
	var->time = in_time();
	var->num_philo = ft_atoi(v[1]);
	var->time_die = ft_atoi(v[2]);
	var->time_eat = ft_atoi(v[3]);
	var->time_sleep = ft_atoi(v[4]);
	if (var->num_philo <= 0 || var->time_die <= 0
		|| var->time_eat <= 0 || var->time_sleep <= 0)
		return (1);
	if (v[5])
	{
		var->must_eat = ft_atoi(v[5]);
		if (var->must_eat <= 0)
			return (1);
	}
	else
		var->must_eat = -1;
	return (0);
}

void	assign_param(t_philo *philo, t_const_philo *var,
	pthread_mutex_t *m, pthread_mutex_t *pr)
{
	int	i;

	i = 0;
	while (i < var->num_philo)
	{
		philo[i].ate = 0;
		philo[i].id = i + 1;
		philo[i].mutex = m;
		philo[i].print = pr;
		philo[i].var = var;
		i++;
	}
}

int	free_param(t_philo *philo, pthread_mutex_t *m, t_const_philo *var)
{
	if (philo)
		free(philo);
	if (m)
		free(m);
	if (var)
		free(var);
	return (1);
}

int	init_param(t_philo *philo, t_const_philo *var)
{
	pthread_mutex_t	*m;
	pthread_mutex_t	pr;
	int				i;

	i = 0;
	m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->num_philo);
	if (!m || !philo)
		return (free_param(philo, m, var));
	while (i < var->num_philo)
		if (pthread_mutex_init(&m[i++], 0))
			return (free_param(philo, m, var));
	if (pthread_mutex_init(&pr, 0))
		return (free_param(philo, m, var));
	assign_param(philo, var, m, &pr);
	return (0);
}
