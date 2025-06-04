
#include <iostream>
#include "tree.h"
#include <time.h>

#define BST
#define MAXBST 10

int main()
{
  srand((unsigned)time(NULL));
  TreeItem* pRoot = NULL;

#ifndef BST
  pRoot = FinalyBalancedTree( 10 );
  #else
  for( int i=0; i<MAXBST; i++)
    FindInsert( &pRoot, rand()% (MAXBST<<1) );
#endif

  printf("preOrder: ");
  preOrder( pRoot );
  printf("\n");

  printf("intOrder: ");
  intOrder( pRoot );
  printf("\n");
  
  printf("postOrder: ");
  postOrder( pRoot );
  printf("\n");

  freeTree2( &pRoot );

  return 0;
}

