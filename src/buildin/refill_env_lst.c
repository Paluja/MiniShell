/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refill_env_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juguerre <juguerre@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:35:22 by juguerre          #+#    #+#             */
/*   Updated: 2024/04/16 20:35:22 by juguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_t_lstclear(t_env_list **envp_lst)
{
	t_env_list	*current;
	t_env_list	*next;

	current = *envp_lst;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*envp_lst = NULL;
}

void	refill_envp_lst(t_data *data, char **new_envp)
{
	(void)new_envp;
	if (data->envp_list)
		ft_t_lstclear(&data->envp_list);
	init_env_list(data, new_envp);
}

int	ft_lstsize_cmd(t_cmd *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != 0)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
