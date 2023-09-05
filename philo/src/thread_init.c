/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 < anrodri2@student.42lyon.fr >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:25:50 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/24 18:35:19 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	value_init(t_philo *philo, t_thread *thread, size_t i)
{
	thread->philo_nb = i;
	thread->time_to_eat = philo->time_to_eat;
	thread->time_to_sleep = philo->time_to_sleep;
	thread->time_to_die = philo->time_to_die;
	thread->eat_count = 0;
	thread->eat_count_max = philo->must_eat;
	thread->is_even = !(i % 2);
	thread->mutex_right_fork = &philo->mutex_array[i];
	if (i == 0)
		i = philo->philo_count;
	thread->mutex_left_fork = &philo->mutex_array[i - 1];
	thread->mutex_printf = &philo->mutex_printf;
	thread->mutex_wait_for_threads = &philo->mutex_wait_for_threads;
}

int	threads_init(t_philo *philo)
{
	int			i;
	t_thread	*thread;
	int			ret_value;

	i = 0;
	ret_value = mutex_init(philo);
	if (ret_value)
		return (ret_value);
	philo->threads_array = malloc(sizeof(pthread_t) * philo->philo_count);
	if (!philo->threads_array)
		return (free(philo->mutex_array), ERR_MEM_ALLOC_FAILED);
	thread = malloc (sizeof(t_thread) * philo->philo_count);
	if (!thread)
		return (free(philo->mutex_array), free(philo->threads_array), ERR_MEM_ALLOC_FAILED);
	pthread_mutex_lock(&philo->mutex_wait_for_threads);
	while (i < philo->philo_count)
	{
		value_init(philo, &thread[i], i);
		if (pthread_create(&philo->threads_array[i], NULL, &thread_main, &thread[i]) != 0)
			return (free(philo->threads_array), ERR_THREAD_FAILED);
		i++;
	}
	pthread_mutex_unlock(&philo->mutex_wait_for_threads);
	ret_value = threads_exit(philo);
	if (ret_value != 0)
		return (ret_value);
	ret_value = mutex_destroy(philo);
	return (ret_value);
}