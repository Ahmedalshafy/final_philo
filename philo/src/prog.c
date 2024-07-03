/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:37:29 by aalshafy          #+#    #+#             */
/*   Updated: 2024/07/03 16:22:58 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	*philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	if (philo->philo_nbr == 1)
	{
		print_messege(philo->id, "has taken a fork", philo);
		ft_usleep(philo->time_to_die, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (!dead_status_check(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

/*eat function*/
void	eating(t_philosophers *philo)
{
	mutux_lock_order(philo);
	pthread_mutex_lock(philo->meal_count_lock);
	philo->last_meal = get_time();
	philo->is_eating = 1;
	philo->meal_count++;
	pthread_mutex_unlock(philo->meal_count_lock);
	print_messege(philo->id, "has taken a fork", philo);
	print_messege(philo->id, "has taken a fork", philo);
	print_messege(philo->id, "is eating", philo);
	*(philo->right_fork) = 0;
	*(philo->left_fork) = 0;
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(philo->meal_count_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->meal_count_lock);
	*(philo->left_fork) = 1;
	*(philo->right_fork) = 1;
	pthread_mutex_unlock(philo->left_fork_lock);
	pthread_mutex_unlock(philo->right_fork_lock);
}

/*sleep function*/
void	sleeping(t_philosophers *philo)
{
	print_messege(philo->id, "is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

/*think function*/
void	thinking(t_philosophers *philo)
{
	print_messege(philo->id, "is thinking", philo);
}

void	mutux_lock_order(t_philosophers *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork_lock);
		pthread_mutex_lock(philo->left_fork_lock);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork_lock);
		pthread_mutex_lock(philo->right_fork_lock);
	}
}
