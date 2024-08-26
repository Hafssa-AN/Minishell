#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct node {
	char *str;
	struct node *next;
	struct node *previous;
} t_node;

size_t ft_strlen(const char *s) {
	size_t i = 0;
	while (s[i]) i++;
	return i;
}

char *ft_strdup(const char *s1) {
	size_t len = ft_strlen(s1) + 1;
	char *str = (char *)malloc(len * sizeof(char));
	return str ? memcpy(str, s1, len) : NULL;
}

char *ft_substr(const char *s, unsigned int start, size_t len) {
	size_t slen = ft_strlen(s);
	if (start >= slen) return ft_strdup("");
	len = (len > slen - start) ? slen - start : len;
	char *substr = (char *)malloc(len + 1);
	if (!substr) return NULL;
	memcpy(substr, s + start, len);
	substr[len] = '\0';
	return substr;
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

t_node *ft_lstnew(char *content) {
	t_node *node = (t_node *)malloc(sizeof(t_node));
	if (!node) return NULL;
	node->str = content;
	node->next = NULL;
	node->previous = NULL;
	return node;
}

void add_node(t_node **head, t_node **tail, char *content) {
	t_node *new_node = ft_lstnew(content);
	if (!*head) {
		*head = new_node;
	} else {
		(*tail)->next = new_node;
		new_node->previous = *tail;
	}
	*tail = new_node;
}

void split_string(t_node **head, t_node **tail, char *str, const char *delim, size_t delim_len) {
	unsigned int i = 0, start = 0;
	while (str[i]) {
		if (strncmp(&str[i], delim, delim_len) == 0) {
			if (i > start) add_node(head, tail, ft_substr(str, start, i - start));
			add_node(head, tail, ft_substr(str, i, delim_len));
			i += delim_len;
			start = i;
		} else {
			i++;
		}
	}
	if (i > start) add_node(head, tail, ft_substr(str, start, i - start));
}

void parth(t_node **head, char *str) {
	t_node *tail = NULL;
	split_string(head, &tail, str, "(", 1);
	split_string(head, &tail, str, ")", 1);
}

void and_or(t_node **head) {
	t_node *tail = NULL;
	t_node *current = *head;
	while (current) {
		t_node *next = current->next;
		split_string(head, &tail, current->str, "&&", 2);
		split_string(head, &tail, current->str, "||", 2);
		free(current->str);
		free(current);
		current = next;
	}
}

void redirect_operators(t_node **head) {
	t_node *tail = NULL;
	t_node *current = *head;
	while (current) {
		t_node *next = current->next;
		split_string(head, &tail, current->str, ">>", 2);
		split_string(head, &tail, current->str, "<<", 2);
		split_string(head, &tail, current->str, ">", 1);
		split_string(head, &tail, current->str, "<", 1);
		free(current->str);
		free(current);
		current = next;
	}
}

void quote_handling(t_node **head) {
	t_node *tail = NULL;
	t_node *current = *head;
	while (current) {
		t_node *next = current->next;
		char *str = current->str;
		unsigned int i = 0, start = 0;
		char quote_type = 0;

		while (str[i]) {
			if ((str[i] == '\'' || str[i] == '\"') && !quote_type) {
				if (i > start) add_node(head, &tail, ft_substr(str, start, i - start));
				quote_type = str[i];
				start = i;
			} else if (str[i] == quote_type) {
				add_node(head, &tail, ft_substr(str, start, i - start + 1));
				quote_type = 0;
				start = i + 1;
			}
			i++;
		}

		if (i > start) add_node(head, &tail, ft_substr(str, start, i - start));

		free(current->str);
		free(current);
		current = next;
	}
}

void split_spaces(t_node **head) {
	t_node *tail = NULL;
	t_node *current = *head;
	while (current) {
		t_node *next = current->next;
		char *str = current->str;
		unsigned int i = 0, start = 0;
		char quote_type = 0;

		while (str[i]) {
			if ((str[i] == '\'' || str[i] == '\"') && !quote_type) {
				quote_type = str[i];
			} else if (str[i] == quote_type) {
				quote_type = 0;
			} else if (str[i] == ' ' && !quote_type) {
				if (i > start) add_node(head, &tail, ft_substr(str, start, i - start));
				add_node(head, &tail, ft_strdup(" "));
				start = i + 1;
			}
			i++;
		}

		if (i > start) add_node(head, &tail, ft_substr(str, start, i - start));

		free(current->str);
		free(current);
		current = next;
	}
}

t_node *ft_split(char *str) {
	t_node *head = NULL;
	t_node *tail = NULL;
	char *trimmed_str = ft_strtrim(str, " ");
	parth(&head, trimmed_str);
	and_or(&head);
	redirect_operators(&head);
	quote_handling(&head);
	split_spaces(&head);
	free(trimmed_str);
	return head;
}

int main(void) {
	char *input;
	t_node *head;

	while (1)
    {
		input = readline("Entrez une commande: ");
		if (!input || strcmp(input, "exit") == 0) {
			free(input);
			break;
		}

		head = ft_split(input);
		free(input);

		while (head) {
			printf("[%s]\n", head->str);
			t_node *temp = head;
			head = head->next;
			free(temp->str);
			free(temp);
		}
	}

	return 0;
}
