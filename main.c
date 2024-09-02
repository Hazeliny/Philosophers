/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:18:13 by linyao            #+#    #+#             */
/*   Updated: 2024/09/02 17:09:25 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_valid_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	if (is_valid_digit(av[1]) == 1 || ft_atoi(av[1]) > MAX_PHILOS \
				|| ft_atoi(av[1]) <= 0)
		return (printf("Incorrect number of philosophers\n"), 1);
	if (is_valid_digit(av[2]) == 1 || ft_atoi(av[2]) <= 0)
		return (printf("Incorrect time to die\n"), 1);
	if (is_valid_digit(av[3]) == 1 || ft_atoi(av[3]) <= 0)
		return (printf("Incorrect time to eat\n"), 1);
	if (is_valid_digit(av[4]) == 1 || ft_atoi(av[4]) <= 0)
		return (printf("Incorrect time to sleep\n"), 1);
	if (av[5] && (is_valid_digit(av[5]) == 1 || ft_atoi(av[5]) <= 0))
	{
		printf("Incorrect number of times each philo must eat\n");
		return (1);
	}
	return (0);
}

void	destroy_mutex(t_meta_shared *meta)
{
	int	i;

	pthread_mutex_destroy(&meta->m_stop);
	pthread_mutex_destroy(&meta->m_eat);
	pthread_mutex_destroy(&meta->m_display);
	pthread_mutex_destroy(&meta->m_dead);
	i = 0;
	while (i < meta->n_philos)
	{
		pthread_mutex_destroy(&meta->philo[i].fork_l);
		pthread_mutex_destroy(meta->philo[i].fork_r);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_meta_shared	meta;

	if (ac != 5 && ac != 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	if (check_args(av) == 1)
		return (1);
	init_meta(&meta, av);
	init_philo(&meta);
	if (manage_philos_lifecycle(&meta) != 0)
		return (1);
	destroy_mutex(&meta);
	return (0);
}
