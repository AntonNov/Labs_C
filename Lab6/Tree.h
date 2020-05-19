#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeItem {
	struct TreeItem* left;
	struct TreeItem* right;
	int info;
	struct TreeItem* prev; /* Корень предыдущего дерева*/
	struct TreeItem* next; /* Корень следующего дерева */
} TreeItem;

/* Список деревьев*/
typedef struct TreeList {
	TreeItem* start;/* Корень первого дерева*/
	TreeItem* end; /* Корень последнего дерева*/
	int count;
} TreeList;

void InitializationTrees(TreeList* list)
{
	list->start = list->end = NULL;

}

/* Возвращает корень дерева*/
TreeItem* TreeAdd(TreeItem *root, TreeItem* r, int info) {
	if (!r) {
		r = (TreeItem*) malloc(sizeof(TreeItem));

		if (!r) {
			printf_s("Memory allocation error\n");
			exit(1);
		}

		r->left = NULL;
		r->right = NULL;
		r->info = info;

		if (!root)
			return r;

		if (info < root->info)
			root->left = r;
		else
			root->right = r;

		return root;
	}

	if (info < r->info)
		return TreeAdd(r, r->left, info);
	else
		return TreeAdd(r, r->right, info);

	return root;
}

void Tree_inorder(TreeItem* root) {
	if (!root)	
		return;
	Tree_inorder(root->left);
	if (root->info)
		printf("%d ", root->info);
	Tree_inorder(root->right);
	printf_s("\n");
}

void Tree_preorder(TreeItem* root) {
	if (!root)
		return;

	if (root->info)
		printf("%d ", root->info);
	printf("(");
	Tree_preorder(root->left);
	printf(",");
	Tree_preorder(root->right);
	printf(")");
}
int Tree_preorder_count(TreeItem* root, int print) {
	if (!root)
		return 0;

	if (root->info && print)
		printf("%d ", root->info);
	auto countl = Tree_preorder_count(root->left, 0);
	auto countr = Tree_preorder_count(root->right, 0);
	if ((countl > 0 || countr > 0) && print) {
		printf("(");
		Tree_preorder_count(root->left, 1);
		if (countl > 0 && countr > 0)
			printf(",");
		Tree_preorder_count(root->right, 1);
		printf(")");
	}

	return countl + countr + 1;
}

void Tree_postorder(TreeItem* root) {
	if (!root)
		return;
	Tree_postorder(root->left);
	Tree_postorder(root->right);
	if (root->info)
		printf("%d ", root->info);
}

TreeItem* Tree_search(TreeItem* root, int key) {
	if (!root)
		return NULL;  /* пустое дерево */

	while (root->info != key) {
		if (key < root->info)
			root = root->left;
		else
			root = root->right;

		if (root == NULL)
			break;
	}

	return root;
}

void Tree_clear(TreeItem* root) {
	if (!root)
		return;

	Tree_clear(root->left);
	Tree_clear(root->right);

	free(root);
}

TreeItem* TreeItemCreate(int info) {
	TreeItem* item = (TreeItem*)malloc(sizeof(TreeItem));
	if (!item) {
		printf("Не хватает памяти\n");
		exit(1);
	}

	item->left = NULL;
	item->right = NULL;
	item->next = NULL;
	item->info = info;

	return item;
}

TreeItem* Tree_Add_not_rec(TreeItem* tree, int info) {
	if (!tree) {
		return TreeItemCreate(info);
	}

	TreeItem* root = tree;
	while (1) 
	{
		if (root->info == info)
			return tree;

		if (info < root->info) {
			if (root->left)
				root = root->left;
			else {
				root->left = TreeItemCreate(info);
				return tree;
			}
		}
		else{
			if (root->right)
				root = root->right;
			else {
				root->right = TreeItemCreate(info);
				return tree;
			}
		}
	}
}

void Insert(TreeItem **tree, TreeItem *item) {
	if (!(*tree)) 
	{
		*tree = item;
		return;
	}
	if (item->info < (*tree)->info)
		Insert(&(*tree)->left, item);
	else if (item->info > (*tree)->info)
		Insert(&(*tree)->right, item);
}
void PrintTree(TreeItem* t, int u) {

	if (t == NULL) return; 

	else 

	{
		PrintTree(t->left, ++u);
		for (int i = 0; i < u; ++i)
			printf_s(" ");

		printf_s("%d\n", t->info);
		u--;

	}
	PrintTree(t->right, ++u);

}
void Delete_Node_BinaryTree(TreeItem** node, int info) {

	if ((*node) != NULL) {

		if ((*node)->info== info) {

			TreeItem* ptr = (*node);

			if ((*node)->left == NULL && (*node)->right == NULL)
				(*node) = NULL;

			else if ((*node)->left == NULL) (*node) = ptr->right;

			else if ((*node)->right == NULL) (*node) = ptr->left;

			else {
				(*node) = ptr->right;

				TreeItem** ptr1;

				ptr1 = node;

				while (*ptr1 != NULL)

				ptr1 = &((*ptr1)->left);

				(*ptr1) = ptr->left;
			}

			Delete_Node_BinaryTree(node, info);
		}

		else {
			Delete_Node_BinaryTree(&((*node)->left), info);

			Delete_Node_BinaryTree(&((*node)->right), info);
		}
	}
}
