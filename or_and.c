/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 04:58:32 by hanebaro          #+#    #+#             */
/*   Updated: 2024/08/26 15:05:13 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct node
{
	char		*str;
	struct	node	*next;
	struct node	*previous;
}t_node;

int ft_strcmp(const char *s1, const char *s2)
{
	size_t i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return 1;
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return -1;
		i++;
	}
	return (0);
}

size_t ft_strlen(const char *s)
{
	size_t i = 0;
	while (s[i])
		i++;
	return i;
}

char *ft_strdup(const char *s1)
{
	char *str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!str)
		return NULL;
	size_t i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return str;
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

static char	*is_null(char const *s1, char const *set)
{
	if (!set)
		return (ft_strdup(s1));
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	t;
	char	*p;

	if (!s1 || !set)
		return (is_null(s1, set));
	i = 0;
	j = ft_strlen(s1);
	t = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (i < j && ft_strchr(set, s1[j - 1]))
		j--;
	p = (char *)malloc(sizeof(char) * j - i + 1);
	if (!p)
		return (NULL);
	while (s1[i] && t < j - i)
	{
		p[t] = s1[i + t];
		t++;
	}
	p[t] = '\0';
	return (p);
}

t_node *ft_lstnew(void *content)
{
	t_node *node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return NULL;
	node->str = content;
	node->next = NULL;
	node->previous = NULL;
	return node;
}



char *ft_substr(char const *s, unsigned int start, size_t len)
{
	if (!s || start >= ft_strlen(s))
		return ft_strdup("");

	size_t newlen = ft_strlen(s + start);
	if (newlen < len)
		len = newlen;

	char *nv = (char *)malloc((len + 1) * sizeof(char));
	if (!nv)
		return NULL;

	size_t i;
	for (i = 0; i < len; i++)
		nv[i] = s[start + i];
	nv[i] = '\0';

	return nv;
}

void parth(t_node **head, char *str)
{
	unsigned int i = 0;
	unsigned int start = 0;
	t_node *tmp = NULL;

	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			if (i > start)
			{
				char *part = ft_substr(str, start, i - start);
				t_node *new_node = ft_lstnew(part);

				if (!*head)
				{
					*head = new_node;
					tmp = *head;
				}
				else
				{
					tmp->next = new_node;
					tmp = new_node;
				}
			}

			char *parenthesis = ft_substr(str, i, 1);
			t_node *parenthesis_node = ft_lstnew(parenthesis);

			if (!*head)
			{
				*head = parenthesis_node;
				tmp = *head;
			}
			else
			{
				tmp->next = parenthesis_node;
				tmp = parenthesis_node;
			}
			start = i + 1;
		}
		i++;
	}

	if (i > start)
	{
		char *part = ft_substr(str, start, i - start);
		t_node *new_node = ft_lstnew(part);

		if (!*head)
		{
			*head = new_node;
		}
		else
		{
			tmp->next = new_node;
		}
	}
}

void and_or(t_node **head)
{
	t_node *current = *head;
	t_node *prev = NULL;

	while (current)
	{
		char *str = current->str;
		t_node *sub_head = NULL;
		t_node *sub_tail = NULL;
		unsigned int i = 0;
		unsigned int start = 0;

		while (str[i])
		{
			if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|'))
			{
				if (i > start)
				{
					char *part = ft_substr(str, start, i - start);
					t_node *new_node = ft_lstnew(part);

					if (!sub_head)
					{
						sub_head = new_node;
						sub_tail = new_node;
					}
					else
					{
						sub_tail->next = new_node;
						new_node->previous = sub_tail;
						sub_tail = new_node;
					}
				}

				char *operator_part = ft_substr(str, i, 2);
				t_node *operator_node = ft_lstnew(operator_part);

				if (!sub_head)
				{
					sub_head = operator_node;
					sub_tail = operator_node;
				}
				else
				{
					sub_tail->next = operator_node;
					operator_node->previous = sub_tail;
					sub_tail = operator_node;
				}

				i++;
				start = i + 1;
			}
			i++;
		}

		if (i > start)
		{
			char *part = ft_substr(str, start, i - start);
			t_node *new_node = ft_lstnew(part);

			if (!sub_head)
			{
				sub_head = new_node;
				sub_tail = new_node;
			}
			else
			{
				sub_tail->next = new_node;
				new_node->previous = sub_tail;
				sub_tail = new_node;
			}
		}

		// Replace the current node with the new sub-list
		if (prev)
			prev->next = sub_head;
		else
			*head = sub_head;

		if (sub_head)
			sub_head->previous = prev;

		prev = sub_tail;
		
		t_node *next = current->next;
		free(current->str);
		free(current);
		current = next;

		if (prev)
			prev->next = current;
		if (current)
			current->previous = prev;
	}
}

void redirect_operators(t_node **head)
{
	t_node *current = *head;
	t_node *prev = NULL;

	while (current)
	{
		char *str = current->str;
		t_node *sub_head = NULL;
		t_node *sub_tail = NULL;
		unsigned int i = 0;
		unsigned int start = 0;

		while (str[i])
		{
			if ((str[i] == '>' && str[i + 1] == '>') || 
				(str[i] == '<' && str[i + 1] == '<') ||
				(str[i] == '>' && str[i + 1] != '>') ||
				(str[i] == '<' && str[i + 1] != '<') ||
				(str[i] == '|' && str[i + 1] != '|') ||
				(str[i] == '|' && str[i + 1] == '|'))
			{
				// Add the part before the operator
				if (i > start)
				{
					char *part = ft_substr(str, start, i - start);
					t_node *new_node = ft_lstnew(part);

					if (!sub_head)
					{
						sub_head = new_node;
						sub_tail = new_node;
					}
					else
					{
						sub_tail->next = new_node;
						new_node->previous = sub_tail;
						sub_tail = new_node;
					}
				}

				// Determine operator length
				int operator_len;
				if (str[i] == '|' && str[i + 1] == '|')
				{
					operator_len = 2;
				}
				else if (str[i] == '|')
				{
					operator_len = 1;
				}
				else if (str[i + 1] == '>' || str[i + 1] == '<')
				{
					operator_len = 2;
				}
				else
				{
					operator_len = 1;
				}

				// Add the operator
				char *operator_part = ft_substr(str, i, operator_len);
				t_node *operator_node = ft_lstnew(operator_part);

				if (!sub_head)
				{
					sub_head = operator_node;
					sub_tail = operator_node;
				}
				else
				{
					sub_tail->next = operator_node;
					operator_node->previous = sub_tail;
					sub_tail = operator_node;
				}

				i += operator_len;
				start = i;
			}
			else
			{
				i++;
			}
		}

		// Add the remaining part after the last operator
		if (i > start)
		{
			char *part = ft_substr(str, start, i - start);
			t_node *new_node = ft_lstnew(part);

			if (!sub_head)
			{
				sub_head = new_node;
				sub_tail = new_node;
			}
			else
			{
				sub_tail->next = new_node;
				new_node->previous = sub_tail;
				sub_tail = new_node;
			}
		}

		// Replace the current node with the new sub-list
		if (prev)
			prev->next = sub_head;
		else
			*head = sub_head;

		if (sub_head)
			sub_head->previous = prev;

		prev = sub_tail;
		
		t_node *next = current->next;
		free(current->str);
		free(current);
		current = next;

		if (prev)
			prev->next = current;
		if (current)
			current->previous = prev;
	}
}

void quote_handling(t_node **head)
{
	t_node *current = *head;
	t_node *prev = NULL;

	while (current)
	{
		char *str = current->str;
		t_node *sub_head = NULL;
		t_node *sub_tail = NULL;
		unsigned int i = 0;
		unsigned int start = 0;
		char quote_type = 0;

		while (str[i])
		{
			if ((str[i] == '\'' || str[i] == '\"') && !quote_type)
			{
				// Start of a quoted section
				if (i > start)
				{
					// Add the part before the quote
					char *part = ft_substr(str, start, i - start);
					t_node *new_node = ft_lstnew(part);
					if (!sub_head)
					{
						sub_head = new_node;
						sub_tail = new_node;
					}
					else
					{
						sub_tail->next = new_node;
						new_node->previous = sub_tail;
						sub_tail = new_node;
					}
				}
				quote_type = str[i];
				start = i;  // Include the opening quote
			}
			else if (str[i] == quote_type)
			{
				// End of a quoted section
				char *quoted_part = ft_substr(str, start, i - start + 1);  // Include the closing quote
				t_node *quoted_node = ft_lstnew(quoted_part);
				if (!sub_head)
				{
					sub_head = quoted_node;
					sub_tail = quoted_node;
				}
				else
				{
					sub_tail->next = quoted_node;
					quoted_node->previous = sub_tail;
					sub_tail = quoted_node;
				}
				quote_type = 0;
				start = i + 1;
			}
			i++;
		}

		// Add any remaining part
		if (i > start)
		{
			char *part = ft_substr(str, start, i - start);
			t_node *new_node = ft_lstnew(part);
			if (!sub_head)
			{
				sub_head = new_node;
				sub_tail = new_node;
			}
			else
			{
				sub_tail->next = new_node;
				new_node->previous = sub_tail;
				sub_tail = new_node;
			}
		}

		// Replace the current node with the new sub-list
		if (prev)
			prev->next = sub_head;
		else
			*head = sub_head;

		if (sub_head)
			sub_head->previous = prev;

		prev = sub_tail;
		
		t_node *next = current->next;
		free(current->str);
		free(current);
		current = next;

		if (prev)
			prev->next = current;
		if (current)
			current->previous = prev;
	}
}

void split_spaces(t_node **head)
{
	t_node *current = *head;
	t_node *prev = NULL;

	while (current)
	{
		char *str = current->str;
		t_node *sub_head = NULL;
		t_node *sub_tail = NULL;
		unsigned int i = 0;
		unsigned int start = 0;
		char quote_type = 0;

		while (str[i])
		{
			if ((str[i] == '\'' || str[i] == '\"') && !quote_type)
			{
				quote_type = str[i];
			}
			else if (str[i] == quote_type)
			{
				quote_type = 0;
			}
			else if (str[i] == ' ' && !quote_type)
			{
				if (i > start)
				{
					// Add the part before the space
					char *part = ft_substr(str, start, i - start);
					t_node *new_node = ft_lstnew(part);
					if (!sub_head)
					{
						sub_head = new_node;
						sub_tail = new_node;
					}
					else
					{
						sub_tail->next = new_node;
						new_node->previous = sub_tail;
						sub_tail = new_node;
					}
				}

				// Add the space itself
				char *space_part = ft_strdup(" ");
				t_node *space_node = ft_lstnew(space_part);
				if (!sub_head)
				{
					sub_head = space_node;
					sub_tail = space_node;
				}
				else
				{
					sub_tail->next = space_node;
					space_node->previous = sub_tail;
					sub_tail = space_node;
				}

				start = i + 1;
			}
			i++;
		}

		// Add the last part after the last space
		if (i > start)
		{
			char *part = ft_substr(str, start, i - start);
			t_node *new_node = ft_lstnew(part);
			if (!sub_head)
			{
				sub_head = new_node;
				sub_tail = new_node;
			}
			else
			{
				sub_tail->next = new_node;
				new_node->previous = sub_tail;
				sub_tail = new_node;
			}
		}

		// Replace the current node with the new sub-list
		if (prev)
			prev->next = sub_head;
		else
			*head = sub_head;

		if (sub_head)
			sub_head->previous = prev;

		prev = sub_tail;
		
		t_node *next = current->next;
		free(current->str);
		free(current);
		current = next;

		if (prev)
			prev->next = current;
		if (current)
			current->previous = prev;
	}
}


t_node *ft_split(char *str)
{
	t_node *head = NULL;
	int i = 0;

	// Skip leading spaces
	str = ft_strtrim(str, " ");
	// Parse the input string and handle parentheses
	parth(&head, &str[i]);

	// Handle logical operators
	and_or(&head);

	redirect_operators(&head);
	quote_handling(&head);
	split_spaces(&head);
	return (head);
}
void my_error()
{
	printf("syntax error");
}

int is_separ(char *str)
{
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, "||") 
	 	|| !ft_strcmp(str, "&&") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, ">>")
		||!ft_strcmp(str, "<") || !ft_strcmp(str, "<<") )
		return(1);
	return(0);
}
int	taille(t_node *head)
{
	int i;

	i = 0;
	while (head->str && !is_separ(head->str))
		i++;
	return (i);
}
void create_cmd(t_node **head)//redirection or cmd
{
	char **cmd;
	int exist;
	int len;
	int i;

	exist = 0;
	i = 0;
	if(!ft_strcmp((*head)->str,"echo"))
		exist = 1;
	len = taille(*head);
	cmd = (char**)malloc(sizeof(char *) * (len + 1));
	if(!cmd)
		return;//???
	while((*head)->str && !is_separ((*head)->str))
	{
		cmd[i++] = (*head)->str;
		*head = (*head) -> next;
	}
}

void check_parth(t_node **head)
{
	
}

int	check_first(t_node *head)
{
	if (!ft_strcmp(head->str,"&") || !ft_strcmp(head->str,"&&")
		|| !ft_strcmp(head->str,"||") || !ft_strcmp(head->str,"|"))
	{
		my_error();
		return (0);
	}
	return (1);
}

int	check(t_node *head)
{
	t_node	*tmp;

	if (!check_first(head))
		return (0);
	tmp = head;
	while (tmp)
	{
		if(!ft_strcmp(tmp->str,"("))
			check_parth(&tmp->next);
		else
			create_cmd(&tmp->next);// crete a node in our tree
	}
}
int main(void)
{
	char *input;
	t_node *head;
	t_node *temp;

	while (1)
	{
		input = readline("Entrez une commande: ");
		if (!input)
			break;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}

		head = ft_split(input);
		free(input);
		// check(head);
		while (head != NULL)
		{
			printf("[%s]\n", head->str);
			temp = head;
			head = head->next;
			free(temp->str);
			free(temp);
		}
	}

	return 0;
}
