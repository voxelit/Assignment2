/*
    Name: Kaitlyn Corpuz, 5006553690, CS 302 - 1004, Assignment #2
    Description: This program defines the properties of an AVL Tree
    Input: defined in main
    Output: data in tree
*/

#ifndef AVLTree_H
#define AVLTree_H

#include <iostream>
using namespace std;

class AVLTree
{
    struct AvlNode
    {
        int element;
        AvlNode *left;
        AvlNode *right;
        int height;
    };

    public:
        /**
         * Constructor
         */
        AVLTree()
        {
            root = nullptr;
        }

        /**
         * Deconstructor
         */
        ~AVLTree()
        {
            eraseNode(root);
        }

        /**
         * Deallocate node
         */
        void eraseNode(AvlNode *t)
        {
            if(t == nullptr)
                return;
            if(t->left != nullptr)
                eraseNode(t->left);
            if(t->right != nullptr)
                eraseNode(t->right);
            if(t->left == nullptr && t->right == nullptr)
                delete t;
        }


        /**
         * Return the height of node t or -1 if nullptr.
         */
        int height(AvlNode *t) const
        {
            return t == nullptr ? -1 : t->height;
        }

        /**
         * Call insert function
         */
        void insertNode(int data)
        {
            if(root == nullptr )
            {
                AvlNode *t = new AvlNode;
                t->element = data;
                t->height = 0;
                t->left = nullptr;
                t->right = nullptr;
                root = t;
            }
            else    
                insert(data, root);
        }


        /**
        * Internal method to insert into a subtree.
        * x is the item to insert.
        * t is the node that roots the subtree.
        * Set the new root of the subtree.
        */
        void insert(const int x, AvlNode *&t)
        {
            if( t == nullptr )
            {
                t = new AvlNode;
                t->element = x;
                t->height = 0;
                t->left = nullptr;
                t->right = nullptr;
            }
            else if( x < t->element )
                insert( x, t->left);
            else if( t->element < x )
                insert( x, t->right);

            balance( t );
        }

        // Assume t is balanced or within one of being balanced
        void balance( AvlNode *&t)
        {
            if( t == nullptr )
                return;

            if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            {
                if( height( t->left->left ) >= height( t->left->right ) )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
            
            }
            else
            {
                if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
                {
                    if( height( t->right->right ) >= height( t->right->left ) )
                        rotateWithRightChild( t );
                    else
                        doubleWithRightChild( t );
                }

                t->height = max( height( t->left ), height( t->right ) ) + 1;
            }
        }

        /**
        * Rotate binary tree node with left child.
        * For AVL trees, this is a single rotation for case 1.
        * Update heights, then set new root.
        */
        void rotateWithLeftChild( AvlNode *& k2 )
        {
            AvlNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
            k1->height = max( height( k1->left ), k2->height ) + 1;
            k2 = k1;
        }

        /**
        * Rotate binary tree node with right child.
        * For AVL trees, this is a single rotation for case 1.
        * Update heights, then set new root.
        */
        void rotateWithRightChild( AvlNode *& k2 )
        {
            AvlNode *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2->height = max( height( k2->right ), height( k2->left ) ) + 1;
            k1->height = max( height( k1->right ), k2->height ) + 1;
            k2 = k1;
        }

        /**
        * Double rotate binary tree node: first left child
        * with its right child; then node k3 with new left child.
        * For AVL trees, this is a double rotation for case 2.
        * Update heights, then set new root.
        */
        void doubleWithLeftChild( AvlNode *& k3 )
        {
            rotateWithRightChild( k3->left );
            rotateWithLeftChild( k3 );
        }

        /**
        * Double rotate binary tree node: first right child
        * with its left child; then node k3 with new right child.
        * For AVL trees, this is a double rotation for case 2.
        * Update heights, then set new root.
        */
        void doubleWithRightChild( AvlNode *& k3 )
        {
            rotateWithLeftChild( k3->right );
            rotateWithRightChild( k3 );
        }

        /**
        *   Call remove function
        */
        void removeNode(int data)
        {
            remove(data, root);
        }

        /**
        * Internal method to remove from a subtree.
        * x is the item to remove.
        * t is the node that roots the subtree.
        * Set the new root of the subtree.
        */
        void remove( const int x, AvlNode *&t )
        {
            if( t == nullptr )
            {
                cout << "Node not found. Please try again. \n\n"; // Item not found; do nothing
                return;
            }


            if( x < t->element )
                remove( x, t->left );
            else if( t->element < x )
                remove( x, t->right );
            else if( t->left != nullptr && t->right != nullptr ) // Two children
            {
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
            else
            {
                AvlNode *oldNode = t;
                t = ( t->left != nullptr ) ? t->left : t->right;
                delete oldNode;
            }

            //balance( t , parent);
        }

        /**
        * Internal method to find the smallest item in a subtree t.
        * Return node containing the smallest item.
        */
        AvlNode * findMin( AvlNode *t ) const
        {
            if( t == nullptr )
                return nullptr;
            if( t->left == nullptr )
                return t;
            return findMin( t->left );
        }

        /*
        *   Print AVL tree
        */
       void print(AvlNode *t, int space, char direction)
       {
            // print nothing if tree is empty
            if (t == nullptr)
                return;
        
            // Increase distance between levels
            space += 10;
            int half = space - 5;
        
            print(t->right, space, '/');
        
            // Print current node after spacing out
            if(direction == '\\')
            {
                for (int i = 10; i <= half; i++)
                    cout << " ";
                cout << direction << endl;
            }
            for (int i = 10; i < space; i++)
                cout << " ";
            cout << t->element << endl;
            if(direction == '/')
            {
                for (int i = 10; i <= half; i++)
                    cout << " ";
                cout << direction << endl;
            }
 
            print(t->left, space, '\\');
       }

       /*
       *    Call print function starting with root node
       */
       void callPrint()
       {
            print(root, 0, ' ');
       }
    private:
    static const int ALLOWED_IMBALANCE = 1;
    AvlNode *root;
};

#endif