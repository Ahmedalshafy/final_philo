/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:29:07 by aalshafy          #+#    #+#             */
/*   Updated: 2024/06/30 14:15:53 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosophers	philos[MAX_PHILOS];
	pthread_mutex_t	forks_mutexes[MAX_PHILOS];
	int				forks[MAX_PHILOS];

	if (argc != 5 && argc != 6)
		return (write(2, "Error: wrong arguments\n", 24), 1);
	if (!check_args(argv))
		return (write(2, "Error: wrong arguments\n", 24), 1);
	if (!init_data(&data, argv, philos, argc))
		return (write(2, "Error: init_data\n", 17), 1);
	if (!init_forks(forks, forks_mutexes, data.philo_nbr))
		return (write(2, "Error: init_forks\n", 18), 1);
	init_philosophers(&data, philos, forks, forks_mutexes);
	if (!init_threads(philos, &data))
		return (destory_mutexes(&data, forks_mutexes, "Error: init_threads\n"),
			1);
	destory_mutexes(&data, forks_mutexes, NULL);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
			return (0);
		i++;
	}
	return (1);
}

void	destory_mutexes(t_data *data, pthread_mutex_t *forks_mutexes, char *str)
{
	int	i;

	if (str)
		write(2, str, ft_strlen(str));
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&forks_mutexes[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_status);
	pthread_mutex_destroy(&data->meal_count_lock);
}

void	print_messege(int id, char *messege, t_philosophers *philos)
{
	pthread_mutex_lock(philos->print);
	if (!dead_status_check(philos))
		printf("%zu %d %s\n", time_stamp(philos->start_time), id, messege);
	pthread_mutex_unlock(philos->print);
}
