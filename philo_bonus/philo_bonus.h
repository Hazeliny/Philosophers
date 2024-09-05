/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:49:20 by linyao            #+#    #+#             */
/*   Updated: 2024/09/05 12:49:15 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>

# define MAX_PHILOS 201
# define FLAG_QUERY 0
# define FLAG_DEATH 1
# define FLAG_STOP 2

typedef struct s_phi
{
	int		id;
	int		n_eaten;
	long int	t_lastmeal;
	pid_t		pid;
	struct s_meta	*meta_s;
}	t_phi;

typedef struct s_meta
{
	int			n_phi;
	int			n_p_eat_fl;
	int			n_eats;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	long int	t_start;
	bool		stop;
	t_phi		phi[MAX_PHILOS];
	sem_t		*sem_fork;
	sem_t		*sem_stop;
	sem_t		*sem_eat;
	sem_t		*sem_display;
	sem_t		*sem_dead;
}	t_meta;

void		handle_error(char *s);
void		init_meta(t_meta *meta, char **av);
void		init_philo(t_meta *meta);
int			manage_philos_lifecycle(t_meta *meta);
int 		ft_atoi1(char *s);
int		 	is_dead(t_phi *phi, int flag);
long long   get_timestamp(void);
void		ft_sleep(int ms);
void		put_msg(t_phi *p, char *s, int num);
#endif
