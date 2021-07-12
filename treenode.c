#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

/// "The  tree  is  a  very  useful  data  structure  whose  name  is  
/// derived  from  the  relationshipbetween its elements. Typically, child 
/// nodes are attached to a parent node."
///
/// "When we add nodes to a tree, it makes sense to add them in a particular order. 
/// This willmake many operations, such as searching, easier. A common ordering is to add a 
/// newnode to a tree such that all of the node’s children possess a value less than the 
/// parentnode and all of the children on the right possess a value greater than the parent node.
/// This is called a binary search tree."
/// (Understanding and Using Pointers, Richard Reese)

typedef struct _node {
  void *data;
  struct _node *left;
  struct _node *right;
} TreeNode;

void insertTreeNode(TreeNode **root, void *data) {
  TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
  node->data = data;
  node->left = NULL;
  node->right = NULL;

  if (*root == NULL) {
    *root = node;
    return;
  } 

  TreeNode *tmp = *root;

  while(1) {
    if (strcmp(tmp->data, data) > 0) {
      if (tmp->left != NULL) {
        tmp = tmp->left; 
      } else {
        tmp->left = node;
        break;
      }
    } else {
      if (tmp->right != NULL) {
        tmp = tmp->right;
      } else {
        tmp->right = node;
        break;
      }
    }
  }
}

void deleteTree(TreeNode *root) {
  if (root != NULL) {
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
  }
}

void inOrder(TreeNode *root) {
  if (root != NULL) {
    inOrder(root->left);
    printf("%s", (char *) root->data);
    inOrder(root->right);
  }
}

void preOrder(TreeNode *root) {
  if (root != NULL) {
    printf("%s", (char *) root->data);
    inOrder(root->left);
    inOrder(root->right);
  }
}

void postOrder(TreeNode *root) {
  if (root != NULL) {
    inOrder(root->right);
    inOrder(root->left);
    printf("%s", (char *) root->data);
  }
}

int main() {
  TreeNode *root = NULL;

  insertTreeNode(&root, "c");
  insertTreeNode(&root, "a");
  insertTreeNode(&root, "d");
  insertTreeNode(&root, "b");
  insertTreeNode(&root, "e");

  inOrder(root);
  printf("\n");
  preOrder(root);
  printf("\n");
  postOrder(root);
  printf("\n");

  deleteTree(root);
  
  return 0;
}

