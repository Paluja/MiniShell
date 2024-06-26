/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:02:05 by pjimenez          #+#    #+#             */
/*   Updated: 2024/05/07 18:47:53 by pjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_cmd_if(t_cmd **cmd_lst, t_cmd **new, int key)
{
	if (!*new || (new && (*new)->command[0] && !(key == TKN_REDIR_APPEND
				|| key == TKN_REDIR_OUT || key == TKN_PIPE)))
	{
		*new = new_cmd();
		add_cmd_back(cmd_lst, *new);
	}
}

void	add_word_cmd(t_cmd **new, t_token **token, int *status, int *fd_in)
{
	while (*token && ((*token)->key == TKN_WORD || (*token)->key == TKN_SQUOTES
			|| ((*token)->key == TKN_DQUOTES)))
	{
		(*new)->command = add_to_command((*new)->command, (*token)->content);
		if (!(*token)->next && handle_redirections(*new, fd_in, token))
		{
			*status = 1;
			break ;
		}
		*token = (*token)->next;
	}
}

void	cmd_create(t_data *data)
{
	t_cmd	*new;
	t_token	*token;
	int		fd_in;
	int		status;

	new = NULL;
	fd_in = 0;
	token = data->token_list;
	status = unexpected_token(token);
	while (token && !status)
	{
		new_cmd_if(&data->cmd_list, &new, token->key);
		add_word_cmd(&new, &token, &status, &fd_in);
		if (token && handle_redirections(new, &fd_in, &token))
		{
			status = 1;
			break ;
		}
		else if (token)
			token = token->next;
	}
	if (!redir_out_last(data->token_list))
		change_cmd_out(data->cmd_list);
	data->status = status_check(status);
}
