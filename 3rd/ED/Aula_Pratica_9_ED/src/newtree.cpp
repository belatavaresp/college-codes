#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <sys/time.h>


typedef struct stat{
  int RR;
  int LL;
  int RL;
  int LR;
} stat_t;

typedef struct node {
  int data;
  struct node * left, * right;
  int ht;
} node;

node * insert(node * , int, stat_t *);
node * Delete(node * , int, stat_t *);
node * newinsert(node * , int, stat_t *);
node * newDelete(node * , int, stat_t *);
void preorder(node * );
void inorder(node * );
void dump(node *, int, char* );
int height(node * );
node * rotateright(node * );
node * rotateleft(node * );
node * RR(node * );
node * LL(node * );
node * LR(node * );
node * RL(node * );
int BF(node * );

int main() {
  node *avl_original = NULL;
  node *avl_modificada = NULL;
  stat_t st_original = {0, 0, 0, 0};
  stat_t st_modificada = {0, 0, 0, 0};

  int operacoes[] = {5, 3, 8, 2, 4, 7, 9, 1, 6};
  int num_operacoes = sizeof(operacoes) / sizeof(operacoes[0]);

  printf("AVL Original:\n");
  for (int i = 0; i < num_operacoes; i++) {
    avl_original = insert(avl_original, operacoes[i], &st_original);
    printf("Inserção: %d\n", operacoes[i]);
    printf("Árvore resultante:\n");
    dump(avl_original, 0, " ");
    printf("\n");
  }

  printf("Estatísticas da AVL Original:\n");
  printf("RR: %d\n", st_original.RR);
  printf("LL: %d\n", st_original.LL);
  printf("RL: %d\n", st_original.RL);
  printf("LR: %d\n", st_original.LR);

  printf("\nAVL Modificada:\n");
  for (int i = 0; i < num_operacoes; i++) {
    avl_modificada = newinsert(avl_modificada, operacoes[i], &st_modificada);
    printf("Inserção: %d\n", operacoes[i]);
    printf("Árvore resultante:\n");
    dump(avl_modificada, 0, " ");
    printf("\n");
  }

  printf("Estatísticas da AVL Modificada:\n");
  printf("RR: %d\n", st_modificada.RR);
  printf("LL: %d\n", st_modificada.LL);
  printf("RL: %d\n", st_modificada.RL);
  printf("LR: %d\n", st_modificada.LR);

  // Realizar operações de remoção
  int remocoes[] = {4, 8, 2};
  int num_remocoes = sizeof(remocoes) / sizeof(remocoes[0]);

  printf("\nRemoções na AVL Original:\n");
  for (int i = 0; i < num_remocoes; i++) {
    avl_original = Delete(avl_original, remocoes[i], &st_original);
    printf("Remoção: %d\n", remocoes[i]);
    printf("Árvore resultante:\n");
    dump(avl_original, 0, " ");
    printf("\n");
  }

  printf("Estatísticas da AVL Original após as remoções:\n");
  printf("RR: %d\n", st_original.RR);
  printf("LL: %d\n", st_original.LL);
  printf("RL: %d\n", st_original.RL);
  printf("LR: %d\n", st_original.LR);

  printf("\nRemoções na AVL Modificada:\n");
  for (int i = 0; i < num_remocoes; i++) {
    avl_modificada = newDelete(avl_modificada, remocoes[i], &st_modificada);
    printf("Remoção: %d\n", remocoes[i]);
    printf("Árvore resultante:\n");
    dump(avl_modificada, 0, " ");
    printf("\n");
  }

  printf("Estatísticas da AVL Modificada após as remoções:\n");
  printf("RR: %d\n", st_modificada.RR);
  printf("LL: %d\n", st_modificada.LL);
  printf("RL: %d\n", st_modificada.RL);
  printf("LR: %d\n", st_modificada.LR);

  return 0;
}

node *newinsert(node *T, int x, stat_t *st) {
  if (T == NULL) {
    T = (node *)malloc(sizeof(node));
    T->data = x;
    T->left = NULL;
    T->right = NULL;
  } else if (x > T->data) { // inserir na subárvore direita
    T->right = insert(T->right, x, st);
    if (BF(T) == -2) {
      if (x > T->right->data) {
        T = RR(T);
        st->RR++;
      } else {
        T = RL(T);
        st->RL++;
      }
    }
  } else if (x < T->data) { // inserir na subárvore esquerda
    T->left = insert(T->left, x, st);
    if (BF(T) == 2) {
      if (x < T->left->data) {
        T = LL(T);
        st->LL++;
      } else {
        T = LR(T);
        st->LR++;
      }
    }
  }
  T->ht = height(T);
  return T;
}

node *newDelete(node *T, int x, stat_t *st) {
  node *p;
  if (T == NULL) {
    return NULL;
  } else if (x > T->data) { // remover da subárvore direita
    T->right = Delete(T->right, x, st);
    if (BF(T) == 2) {
      if (BF(T->left) >= 0) {
        T = LL(T);
        st->LL++;
      } else {
        T = LR(T);
        st->LR++;
      }
    }
  } else if (x < T->data) { // remover da subárvore esquerda
    T->left = Delete(T->left, x, st);
    if (BF(T) == -2) {
      if (BF(T->right) <= 0) {
        T = RR(T);
        st->RR++;
      } else {
        T = RL(T);
        st->RL++;
      }
    }
  } else {
    // o nó a ser removido foi encontrado
    if (T->right != NULL) { // remover o sucessor inordem
      p = T->right;
      while (p->left != NULL)
        p = p->left;
      T->data = p->data;
      T->right = Delete(T->right, p->data, st);
      if (BF(T) == 2) { // reequilibrar durante a finalização
        if (BF(T->left) >= 0) {
          T = LL(T);
          st->LL++;
        } else {
          T = LR(T);
          st->LR++;
        }
      }
    } else
      return T->left;
  }
  T->ht = height(T);
  return T;
}

node * insert(node * T, int x, stat_t * st) {
  if (T == NULL) {
    T = (node * ) malloc(sizeof(node));
    T -> data = x;
    T -> left = NULL;
    T -> right = NULL;
  } else
  if (x > T -> data) // insert in right subtree
  {
    T -> right = insert(T -> right, x, st);
    if (BF(T) == -2){
      if (x > T -> right -> data){
        T = RR(T);
	st->RR++;
      } else{
        T = RL(T);
	st->RL++;
      }
    }
  } else
  if (x < T -> data) {
    T -> left = insert(T -> left, x, st);
    if (BF(T) == 2){
      if (x < T -> left -> data){
        T = LL(T);
	st->LL++;
      }else{
        T = LR(T);
	st->LR++;
      }
    }
  }
  T -> ht = height(T);
  return (T);
}

node * Delete(node * T, int x, stat_t * st) {
  node * p;
  if (T == NULL) {
    return NULL;
  } else
  if (x > T -> data) // insert in right subtree
  {
    T -> right = Delete(T -> right, x, st);
    if (BF(T) == 2){
      if (BF(T -> left) >= 0){
        T = LL(T);
	st->LL++;
      }
      else{
        T = LR(T);
	st->LR++;
      }
    }
  } else
  if (x < T -> data) {
    T -> left = Delete(T -> left, x, st);
    if (BF(T) == -2){ //Rebalance during windup
      if (BF(T -> right) <= 0){
        T = RR(T);
	st->RR++;
      }
      else{
        T = RL(T);
	st->RL++;
      }
    }
  } else {
    //data to be deleted is found
    if (T -> right != NULL) { //delete its inorder succesor
      p = T -> right;
      while (p -> left != NULL)
        p = p -> left;
      T -> data = p -> data;
      T -> right = Delete(T -> right, p -> data, st);
      if (BF(T) == 2){ //Rebalance during windup
        if (BF(T -> left) >= 0){
          T = LL(T);
	  st->LL++;
	}
        else{
          T = LR(T);\
	  st->LR++;
	}
      }
    } else
      return (T -> left);
  }
  T -> ht = height(T);
  return (T);
}

int height(node * T) {
  int lh, rh;
  if (T == NULL)
    return (0);
  if (T -> left == NULL)
    lh = 0;
  else
    lh = 1 + T -> left -> ht;
  if (T -> right == NULL)
    rh = 0;
  else
    rh = 1 + T -> right -> ht;
  if (lh > rh)
    return (lh);
  return (rh);
}

node * rotateright(node * x) {
  node * y;
  y = x -> left;
  x -> left = y -> right;
  y -> right = x;
  x -> ht = height(x);
  y -> ht = height(y);
  return (y);
}

node * rotateleft(node * x) {
  node * y;
  y = x -> right;
  x -> right = y -> left;
  y -> left = x;
  x -> ht = height(x);
  y -> ht = height(y);
  return (y);
}

node * RR(node * T) {
  T = rotateleft(T);
  return (T);
}

node * LL(node * T) {
  T = rotateright(T);
  return (T);
}

node * LR(node * T) {
  T -> left = rotateleft(T -> left);
  T = rotateright(T);
  return (T);
}

node * RL(node * T) {
  T -> right = rotateright(T -> right);
  T = rotateleft(T);
  return (T);
}

int BF(node * T) {
  int lh, rh;
  if (T == NULL)
    return (0);

  if (T -> left == NULL)
    lh = 0;
  else
    lh = 1 + T -> left -> ht;

  if (T -> right == NULL)
    rh = 0;
  else
    rh = 1 + T -> right -> ht;

  return (lh - rh);
}

void preorder(node * T) {
  if (T != NULL) {
    printf("%d(Bf=%d)", T -> data, BF(T));
    preorder(T -> left);
    preorder(T -> right);
  }
}

void inorder(node * T) {
  if (T != NULL) {
    inorder(T -> left);
    printf("%d(Bf=%d)", T -> data, BF(T));
    inorder(T -> right);
  }
}

void dump(node * T, int level,char * pref) {
  if (T != NULL) {
    printf("%s ",pref);
    for(int i=0; i<level; i++) printf("    ");
    printf("%3d (Bf=%d, H=%d)\n", T -> data, BF(T),T->ht);
    dump(T -> left,level+1,pref);
    dump(T -> right,level+1,pref);
  }
}
