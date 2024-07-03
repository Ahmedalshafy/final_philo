/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalshafy <aalshafy@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:14:04 by aalshafy          #+#    #+#             */
/*   Updated: 2024/07/03 16:18:19 by aalshafy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_PHILOS 200

typedef struct s_philosophers
{
	int				id;
	int				philo_nbr;
	int				*left_fork;
	int				*right_fork;
	int				*dead;
	int				is_eating;
	int				meal_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			last_meal;
	size_t			start_time;
	pthread_t		th;
	pthread_mutex_t	*left_fork_lock;
	pthread_mutex_t	*right_fork_lock;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead_status;
	pthread_mutex_t	*meal_count_lock;
}					t_philosophers;

typedef struct s_data
{
	int				philo_nbr;
	int				meal_nbr;
	int				is_dead;
	t_philosophers	*philos;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_status;
	pthread_mutex_t	meal_count_lock;
	pthread_t		checks;
}					t_data;

int					ft_atoi(char *str);
size_t				ft_strlen(char *str);
size_t				get_time(void);
int					ft_usleep(size_t time, t_philosophers *philo);
size_t				time_stamp(size_t start_time);
int					check_args(char **argv);
int					init_forks(int *forks, pthread_mutex_t *forks_mutexes,
						int philo_nbr);
int					init_threads(t_philosophers *philos, t_data *data);
void				init_philosophers(t_data *data, t_philosophers *philos,
						int *forks, pthread_mutex_t *forks_mutexes);
int					init_data(t_data *data, char **argv, t_philosophers *philos,
						int argc);
void				*check_status(void *arg);
int					check_die(t_philosophers *philos, t_data *data);
int					check_eat_time(t_philosophers *philos, t_data *data);
void				print_messege(int id, char *messege,
						t_philosophers *philos);
void				*philo_routine(void *arg);
int					dead_status_check(t_philosophers *philo);
void				eating(t_philosophers *philo);
void				mutux_lock_order(t_philosophers *philo);
void				sleeping(t_philosophers *philo);
void				thinking(t_philosophers *philo);
void				destory_mutexes(t_data *data,
						pthread_mutex_t *forks_mutexes, char *str);
