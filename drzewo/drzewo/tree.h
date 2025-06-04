
#ifndef TREE_H
#define TREE_H


typedef struct tagTreeItem {
  int key;
  tagTreeItem* pLeft; //wska�nik na lewy element
  tagTreeItem* pRight; // na prawy

} TreeItem, *LP_TreeItem; // naraz dea typy

/*
typedef TreeIrem* LP_TreeItem;*/

void preOrder( TreeItem* pRoot );
void intOrder( TreeItem* pRoot );
void postOrder( TreeItem* pRoot );

TreeItem* FinalyBalancedTree( int n ); // buduje drzewo dok�adnie wywazone o n elementach

void freeTree1( TreeItem* pRoot );
void freeTree2( TreeItem** pRoot ); // po zwolnieniu pamieci nulowany wskaznik do drzewa
TreeItem* freeTree3( TreeItem* pRoot ); 

//!--------------------drzewo BST - Binary Search Tree
// dla kazdego wezla drzewa elemenrt w lewym poddrzewie s� mniejsze od info w�z�a
// a w prawym wieksze

void FindInsert( TreeItem** pRoot, int x );

#endif
