/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:39:42 by aalshafy          #+#    #+#             */
/*   Updated: 2024/07/02 20:52:28 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error: gettimeofday\n", 20);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

size_t	time_stamp(size_t start_time)
{
	return (get_time() - start_time);
}

int	ft_usleep(size_t time, t_philosophers *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (dead_status_check(philo))
			return (0);
		usleep(500);
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
