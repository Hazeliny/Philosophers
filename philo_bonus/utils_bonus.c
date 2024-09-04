/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:14:17 by linyao            #+#    #+#             */
/*   Updated: 2024/09/04 16:54:15 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi1(char *s)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\v' || \
				*s == '\f' || *s == '\r')
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
		result = result * 10 + (*s++ - '0');
	return (sign * result);
}

int	is_dead(t_phi *phi, int flag)
{
	sem_wait(phi->meta_s->sem_dead);
	if (flag)
		phi->meta_s->stop = true;
	if (phi->meta_s->stop)
	{
		sem_post(phi->meta_s->sem_dead);
		return (1);
	}
	sem_post(phi->meta_s->sem_dead);
	return (0);
}

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(int ms)
{
	long int	time;

	time = get_timestamp();
	while (get_timestamp() - time < ms)
		usleep(ms / 20);
}

void	put_msg(t_phi *p, char *s, int num)
{
	sem_wait(p->meta_s->sem_display);
	if (!p->meta_s->stop && !is_dead(p, FLAG_QUERY))
	{
		if (num < 0)
			printf("%d %lld %s\n", p->id, (get_timestamp() - \
					p->meta_s->t_start), s);
		else
			printf("%d %lld %s ------%d times\n", p->id, (get_timestamp() - \
					p->meta_s->t_start), s, num);
	}
	sem_post(p->meta_s->sem_display);
}
