/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:49:20 by linyao            #+#    #+#             */
/*   Updated: 2024/09/03 16:12:08 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>

# define MAX_PHILOS 201

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
	int	n_phi;
	int	n_p_eat_fl;
	int	n_eats;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	long int	t_start;
	bool		stop;
	t_phi		phi[MAX_PHILOS];
	sem_t		sem_fork;
	sem_t           sem_stop;
	sem_t           sem_eat;
	sem_t           sem_display;
	sem_t           sem_dead;
}	t_meta;

#endif
