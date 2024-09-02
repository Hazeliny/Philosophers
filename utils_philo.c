/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:59:22 by linyao            #+#    #+#             */
/*   Updated: 2024/09/02 16:35:42 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *s)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\v' \
		|| *s == '\f' || *s == '\r')
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
		result = result * 10 + (*s++ - '0');
	return (sign * result);
}

int	is_dead(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->meta_shared->m_dead);
	if (flag)
		philo->meta_shared->stop = true;
	if (philo->meta_shared->stop)
	{
		pthread_mutex_unlock(&philo->meta_shared->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->meta_shared->m_dead);
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

void	put_msg(t_philo *p, char *s, int num)
{
	pthread_mutex_lock(&p->meta_shared->m_display);
	if (!p->meta_shared->stop && !is_dead(p, FLAG_QUERY))
	{
		if (num < 0)
			printf("%d %lld %s\n", p->id, (get_timestamp() - \
				p->meta_shared->time_start), s);
		else
			printf("%d %lld %s ------%d times\n", p->id, \
			(get_timestamp() - p->meta_shared->time_start), s, num);
	}
	pthread_mutex_unlock(&p->meta_shared->m_display);
}
