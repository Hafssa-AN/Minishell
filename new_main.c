#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct node
{
	char        *str;
	struct node *next;
	struct node *previous;
} t_node;

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

t_node *ft_lstnew(void *content)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str = content;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s1)
{
	char    *str;
	size_t  i;

	i = 0;
	str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char    *nv;
	size_t  i;
	size_t  newlen;

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
		nv[i] = s[start + i];
		i++;
	}
	nv[i] = '\0';
	return (nv);
}

void parth(t_node **head, char *str)
{
	unsigned int i;
	unsigned int start;
	t_node *tmp;

	i = 0;
	start = 0;
	tmp = NULL;

	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			if (i > start)
			{
				if (!*head)
				{
					*head = ft_lstnew(ft_substr(str, start, i - start));
					tmp = *head;
				}
				else
				{
					tmp->next = ft_lstnew(ft_substr(str, start, i - start));
					tmp = tmp->next;
				}
			}
			if (!*head)
			{
				*head = ft_lstnew(ft_substr(str, i, 1));
				tmp = *head;
			}
			else
			{
				tmp->next = ft_lstnew(ft_substr(str, i, 1));
				tmp = tmp->next;
			}
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		if (!*head)
		{
			*head = ft_lstnew(ft_substr(str, start, i - start));
		}
		else
		{
			tmp->next = ft_lstnew(ft_substr(str, start, i - start));
		}
	}
}

void and_or(t_node **head)
{
	t_node *current = *head;
	t_node *new_head = NULL;
	t_node *new_tail = NULL;

	while (current)
	{
		char *str = current->str;
		unsigned int i = 0;
		unsigned int start = 0;

		while (str[i])
		{
			if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|'))
			{
				// Handle the part before the operator
				if (i > start)
				{
					char *part = ft_substr(str, start, i - start);
					t_node *new_node = ft_lstnew(part);

					if (!new_head)
					{
						new_head = new_node;
						new_tail = new_node;
					}
					else
					{
						new_tail->next = new_node;
						new_tail = new_node;
					}
				}

				// Handle the operator
				char *operator_part = ft_substr(str, i, 2);
				t_node *operator_node = ft_lstnew(operator_part);

				if (!new_head)
				{
					new_head = operator_node;
					new_tail = operator_node;
				}
				else
				{
					new_tail->next = operator_node;
					new_tail = operator_node;
				}

				i++;
				start = i + 1;
			}
			i++;
		}

		// Handle the remaining part after the last operator
		if (i > start)
		{
			char *part = ft_substr(str, start, i - start);
			t_node *new_node = ft_lstnew(part);

			if (!new_head)
			{
				new_head = new_node;
				new_tail = new_node;
			}
			else
			{
				new_tail->next = new_node;
				new_tail = new_node;
			}
		}

		// Replace the current node with the new list
		free(current->str);
		current->str = NULL;
		current->next = new_head;
		new_head = NULL;
		new_tail = NULL;

		current = current->next;
	}
}


t_node *ft_split(char *str)
{
	t_node *head;
	t_node *tmp;
	int	i;

	i = 0;
	while(str[i] && str[i] == ' ')
		i++;
	head = NULL;

	parth(&head, &str[i]);
	and_or(&head);
	return (head);
}

int main(void)
{
	char *input;
	t_node *head;

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
		while (head != NULL)
		{
			printf("%s\n", head->str);
			t_node *temp = head;
			head = head->next;
			free(temp->str);
			free(temp);
		}
	}
	return (0);
}

// void and_or(t_node **head, char *str)
// {
// 	unsigned int i;
// 	unsigned int start;
// 	t_node *tmp;

// 	i = 0;
// 	start = 0;
// 	tmp = NULL;
// 		while (str[i])
// 		{
// 			if ((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|'))
// 			{
// 				if (i > start)
// 				{
// 					if (!*head)
// 					{
// 						*head = ft_lstnew(ft_substr(str, start, i - start));
// 						tmp = *head;
// 					}
// 					else
// 					{
// 						tmp->next = ft_lstnew(ft_substr(str, start, i - start));
// 						tmp = tmp->next;
// 					}
// 				}
// 				if (!*head)
// 				{
// 					*head = ft_lstnew(ft_substr(str, i, 2));
// 					tmp = *head;
// 				}
// 				else
// 				{
// 					tmp->next = ft_lstnew(ft_substr(str, i, 2));
// 					tmp = tmp->next;
// 				}
// 				i++;
// 				start = i + 1;
// 			}
// 			i++;
// 		}
// 		if (i > start)
// 		{
// 			if (!*head)
// 			{
// 				*head = ft_lstnew(ft_substr(str, start, i - start));
// 			}
// 			else
// 			{
// 				tmp->next = ft_lstnew(ft_substr(str, start, i - start));
// 			}
// 		}
// }