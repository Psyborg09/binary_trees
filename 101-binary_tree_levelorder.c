#include "binary_trees.h"

void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int));
levelorder_queue_t *create_node(binary_tree_t *node);
void pint_push(binary_tree_t *node, levelorder_queue_t *head,
		levelorder_queue_t **tail, void (*func)(int));
void free_queue(levelorder_queue_t *head);
void pop(levelorder_queue_t **head);

/**
 * binary_tree_levelorder - Goes through a bin-tree by level-order traversal.
 *
 * @tree: this is A pointer to the root node of the tree to traverse.
 * @func: this is A pointer to a function to call for each node.
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	levelorder_queue_t *q_head, *q_tail;

	if (tree == NULL || func == NULL)
		return;

	q_head = q_tail = create_node((binary_tree_t *)tree);
	if (q_head == NULL)
		return;

	while (q_head != NULL)
	{
		pint_push(q_head->node, q_head, &q_tail, func);
		pop(&q_head);
	}
}

/**
 * create_node - Creates a new levelorder_queue_t node.
 *
 * @node: this si The binary tree node for the new node to contain.
 *
 * Return: If an error occurs, NULL.
 * Otherwise, a pointer to the new node.
 */
levelorder_queue_t *create_node(binary_tree_t *node)
{
	levelorder_queue_t *q_node;

	q_node = malloc(sizeof(levelorder_queue_t));
	if (q_node == NULL)
		return (NULL);

	q_node->node = node;
	q_node->next = NULL;

	return (q_node);
}

/**
 * pint_push - Runs a function on a given binary tree node and
 *             pushes its children into a levelorder_queue_t queue.
 *
 * @node: this is The binary tree node to print and push.
 * @head: this is A double pointer to the head of the queue.
 * @tail: this is A double pointer to the tail of the queue.
 * @func: this is A pointer to the function to call on @node.
 *
 * Description: Upon malloc failure, exits with a status code of 1.
 */
void pint_push(binary_tree_t *node, levelorder_queue_t *head,
		levelorder_queue_t **tail, void (*func)(int))
{
	levelorder_queue_t *new;

	func(node->n);
	if (node->left != NULL)
	{
		new = create_node(node->left);
		if (new == NULL)
		{
			free_queue(head);
			exit(1);
		}
		(*tail)->next = new;
		*tail = new;
	}
	if (node->right != NULL)
	{
		new = create_node(node->right);
		if (new == NULL)
		{
			free_queue(head);
			exit(1);
		}
		(*tail)->next = new;
		*tail = new;
	}
}

/**
 * free_queue - this Frees a levelorder_queue_t queue.
 *
 * @head: thhis is A pointer to the head of the queue.
 */
void free_queue(levelorder_queue_t *head)
{
	levelorder_queue_t *temp_var;

	while (head != NULL)
	{
		temp_var = head->next;
		free(head);
		head = temp_var;
	}
}

/**
 * pop - Pops the head of a levelorder_queue_t queue.
 *
 * @head: this is A double pointer to the head of the queue.
 */
void pop(levelorder_queue_t **head)
{
	levelorder_queue_t *temp_var;

	temp_var = (*head)->next;
	free(*head);
	*head = temp_var;
}
