/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:51:42 by hanebaro          #+#    #+#             */
/*   Updated: 2024/08/23 12:00:19 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct node
{
	char		*str;
	struct node	*next;
	struct node	*previous;
}t_node;

t_node	*ft_lstnew(void *content)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node -> str = content;
	node -> next = NULL;
	node -> previous = NULL;
	return (node);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nv;
	size_t	i;
	size_t	newlen;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || !len)
		return (ft_strdup(""));
	newlen = ft_strlen(s + start);
	if (newlen < len)
		len = newlen;
	nv = (char *)malloc(sizeof(char) * (len + 1));
	if (!nv)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		*(nv + i) = *(s + (start + i));
		i++;
	}
	nv[i] = '\0';
	return (nv);
}

void	parth(t_node *head, char *str)
{
	unsigned int	i;
	unsigned int	start;
	t_node			*tmp;

	i = 0;
	tmp = head;
	start = i;
	while (str[i])
	{
		if (str[i] == '(')
		{
			if (str[i - 1])
			{
				tmp -> next = ft_lstnew(ft_substr(str, start, i - start + 1));
				tmp = tmp -> next;
			}
			tmp -> next = ft_lstnew(ft_substr(str, i, 1));
			start = i + 1;
		}
		else if (str[i] == ')')
		{
			if (str[i - 1] && str[i - 1] != '(')
			{
				tmp -> next = ft_lstnew(ft_substr(str, start, i - start + 1));
				tmp = tmp -> next;
			}
			tmp -> next = ft_lstnew(ft_substr(str, i, 1));
			start = i + 1;
		}
		i++;
	}
	while(head != NULL)
	{
		printf("%s\n",head -> str);
		head = head->next;
	}
	exit(1);
}

t_node	*ft_split(char *str)
{
	t_node	*head;

	head = NULL;
	// supp_sp();
	parth(head, str);
	if(head == NULL)
		printf("is NULL\n");
	return(head);
}

int	main(void)
{
	char	*input;
	t_node	*head;
	
	while (ft_strcmp(input, "exit") != 0)
	{
		input = readline("Entrez une commande: ");
		// printf("%s\n",input);
		head = ft_split(input);
		while(head != NULL)
		{
			printf("%s\n",head -> str);
			head = head->next;
		}
	}
	return (0);
}
