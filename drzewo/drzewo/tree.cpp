#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void Visit( TreeItem* pRoot )
{
  printf( "key: %d\n", pRoot->key );
}

void FindInsert( TreeItem** pRoot, int x )
{
  if( !pRoot )
  {
    // tworzymy nowy element
    *pRoot = (TreeItem*)calloc( 1, sizeof(TreeItem) );
    (*pRoot)->key = x;
    // (*pRoot)->pLeft = (*pRoot)->pRight = NULL; // nie trzeba bo calloc, dla malloc musi byæ
  }
  else if( x < (*pRoot)->key )
    FindInsert( (&(*pRoot)->pLeft), x );
  else if( x > (*pRoot)->key )
    FindInsert( (&(*pRoot)->pRight), x );
  else Visit( *pRoot ); // jest w drzewie to odwiedzamy ten wierzcho³ek (jakas operacja)
}

void preOrder( TreeItem* pRoot )
{
  if( !pRoot ) return; // koniec przegladania pRoot
  printf( "%d ", pRoot->key ); // operacja na wezle
  preOrder( pRoot-> pLeft );
  preOrder( pRoot-> pRight );
}

void intOrder( TreeItem* pRoot )
{
  if( !pRoot ) return; // koniec przegladania pRoot

  intOrder( pRoot-> pLeft );
  printf( "%d ", pRoot->key ); // operacja na wezle
  intOrder( pRoot-> pRight );
}

void postOrder( TreeItem* pRoot )
{
  if( !pRoot ) return; // koniec przegladania pRoot

  postOrder( pRoot-> pLeft );
  postOrder( pRoot-> pRight );
  printf( "%d ", pRoot->key ); // operacja na wezle
}

TreeItem* FinalyBalancedTree( int n )
{
  if( n<1 ) return NULL;
  
  int nl = n/2;
  int np = n - nl - 1;

  TreeItem* v = (TreeItem*)calloc( 1, sizeof( TreeItem ) );
  if ( !v ) return NULL;
  v->key = rand() % ( n<<1 );
  //v->pLeft = v->pRight = NULL; 
  //! gdyby malloc trzeba wyzerowac, calloc zeruje automatycznie
  
  v->pLeft = FinalyBalancedTree( nl );
  v->pRight = FinalyBalancedTree( np );
  return v;
}

void freeTree1( TreeItem* pRoot ) // zwalnianie drzewa w postOrder (od lisci)
{
  if( !pRoot ) return;
  freeTree1( pRoot->pLeft );
  freeTree1( pRoot->pRight );

  // ewentualnie zwolnic pole dynamiczne TreeIrem
  free( pRoot );
}

void freeTree2( TreeItem** pRoot )
{
  if( !pRoot ) return;
  freeTree2( &((*pRoot)->pLeft) );
  freeTree2( &((*pRoot)->pRight) );

  // ewentualnie zwolnic pole dynamiczne TreeIrem
  free( *pRoot );
  *pRoot = NULL;
}

TreeItem* freeTree3( TreeItem* pRoot )
{
  if( pRoot ) {
  pRoot->pLeft = freeTree3( pRoot->pLeft );
  freeTree3( pRoot->pRight ); // nie wykorzystuje wawrtosci zwracanej
  // ewentualnie zwolnic pole dynamiczne TreeIrem
  free( pRoot );
  }

  return NULL;
}

