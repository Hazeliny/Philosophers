/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:16:24 by linyao            #+#    #+#             */
/*   Updated: 2024/09/02 16:29:04 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILOS 201
# define FLAG_QUERY 0
# define FLAG_DEATH 1
# define FLAG_STOP 2

typedef struct s_philo
{
	int						id;
	int						n_eaten;//Number of times he has eaten
	long int				t_lastmeal;//time when he ate last time
	pthread_t				thread;
	struct s_meta_shared	*meta_shared;
	pthread_mutex_t			fork_l;
	pthread_mutex_t			*fork_r;
}	t_philo;

typedef struct s_meta_shared
{
	int				n_philos;
	int				n_p_eat_fl;//N of phis who have eaten full times
	int				n_eats;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	long int		time_start;
	bool			stop;
	t_philo			philo[MAX_PHILOS];
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_display;
	pthread_mutex_t	m_dead;
}	t_meta_shared;

int			ft_atoi(char *s);
void		init_meta(t_meta_shared *meta, char **av);
void		init_philo(t_meta_shared *meta);
int			manage_philos_lifecycle(t_meta_shared *meta);
long long	get_timestamp(void);
void		ft_sleep(int ms);
void		put_msg(t_philo *p, char *s, int num);
int			is_dead(t_philo *philo, int flag);

#endif
