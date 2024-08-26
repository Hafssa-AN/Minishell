/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:43:25 by hanebaro          #+#    #+#             */
/*   Updated: 2024/07/26 19:54:45 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct box
{
	char		*cont;
	struct box	*left;
	struct box	*right;
}	t_noeud;

noeud	*create(char *str)
{
	noeud	*node;

	node = (t_noeud *)malloc(sizeof(t_noeud));
	if (!node)
		return (0);
	node->cont = str;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_noeud	*insert_left(t_noeud *racine, char *str)
{
	racine->left = create(str);
	return (racine->left);
}

t_noeud	*insert_right(t_noeud *racine, char *str)
{
	if(str == "NULL" || str == "null")
		racine->right = NULL;
	racine->right = create(str);
	return (racine->right);
}

t_noeud	*racine(int *x)
{
	char	*str;

	printf("la racine");
	scanf("%s", str);
	x++;
	return (create(char *str));
}

void	extrem(t_noeud *racine)
{
	printf("la gauche");
	scanf("%s", str);
	printf("la droite");
	scanf("%s", str);
}

int	main(void)
{
	t_noeud	*node;
	inr	nbr;

	printf("nombre des noeuds");
	scanf("%d", nbr);
	node = racine(&nbr);
	extrem(node);
}
