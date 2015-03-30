// This program was written entirely by Franciszek Jemioło (index number 346919).
#ifndef _FUN_TREE_H_
#define _FUN_TREE_H_

#include <memory>
#include <iostream>
#include <functional>


template <class T>
class FunTree
{
    private:
        // Nodes hold copies of elements.
        struct Node
        {
            T element;
            std::shared_ptr<Node> left;
            std::shared_ptr<Node> right;
        };
        
        std::shared_ptr<Node> BuildNode (T element)
        {
            std::shared_ptr<Node> nd (new Node);
            nd->left = nullptr;
            nd->right = nullptr;
            nd->element = element;
            return nd;
        }
        
        std::shared_ptr<Node> CopyTree (std::shared_ptr<Node> nd)
        {
            if (nd != nullptr)
            {
                std::shared_ptr<Node> newnd (new Node);
                newnd->element = nd->element;
                newnd->left = CopyTree (nd->left);
                newnd->right = CopyTree (nd->right);    
                return newnd;
            }
            else
            {
                return nd;
            }
        }          

    public:
        // Masked std::functions
        using Comparator = std::function<bool (T, T)>;
        using Predicate = std::function<bool (T)>;
        using Operator = std::function<void (T)>;
        using UnaryOperator = std::function<T (T)>;
        using BinaryOperator = std::function<T (T, T)>;
    
    private:
        using Traversal = std::function<void (std::shared_ptr<Node>, Operator)>;
    
    public:    
        
        std::shared_ptr<Node> root = nullptr;
    
        // Constructors
        FunTree () {}

        FunTree (FunTree<T> const& other)
        {
            root = CopyTree (other.root);
        }
        
        FunTree (FunTree<T>&& other) : root (std::move (other.root)) {}
        
        FunTree<T>& operator= (const FunTree<T>& other)
        {
            if (this == &other)
                return *this;
                
            this->root = CopyTree (other.root);
            return *this;
        }
        
        FunTree<T>& operator= (FunTree<T>&& other)
        {
            this->root = CopyTree (other.root);
            return *this;
        }
        

        static Traversal preorder, inorder, postorder;
    private:
        static Traversal defaultTraversal; 
            
    public:      
             
        // Tree handle
        
        // Inserts copy of an element to very funny tree.
        void insert (T const& element, Comparator const& cmp = std::less<T> ())
        {
            if (root == nullptr)
            {
                root = BuildNode (element);
                return;
            }
            std::shared_ptr<Node> previous, actual = root;
            bool wasLeft;
            while (actual != nullptr)
            {
                previous = actual;
                if (cmp (element, actual->element))
                {
                    actual = actual->left;
                    wasLeft = true;
                }
                else
                {
                    actual = actual->right;
                    wasLeft = false;
                }
            }
            if (wasLeft)
                previous->left = BuildNode (element);
            else
                previous->right = BuildNode (element);
        }
        
        // Returns true if element is in very funny tree.
        bool find 
            (T const& element, Comparator const& cmp = std::less<T> ()) const
        {
            std::shared_ptr<Node> actual = root;
            while (actual != nullptr)
            {
                if (cmp (element, actual->element))
                    actual = actual->left;
                else if (cmp (actual->element, element))
                    actual = actual->right;
                else
                    return true;
            }
            return false;
        }
        
        // Removes element, if it exists, and remove it's subtrees.
        void erase (T const& element, Comparator const& cmp = std::less<T> ())
        {
            if (root != nullptr)
            {
                if ((!cmp (element, root->element)) && 
                    (!cmp (root->element, element)))
                {
                    root = nullptr;
                }
                else
                {
                    std::shared_ptr<Node> actual = root, previous = nullptr;
                    bool wasLeft;
                    while (actual != nullptr)
                    {
                        if (cmp (element, actual->element))
                        {
                            previous = actual;
                            actual = actual->left;
                            wasLeft = true;
                        }
                        else if (cmp (actual->element, element))
                        {
                            previous = actual;
                            actual = actual->right;
                            wasLeft = false;
                        }
                        else
                        {
                            if (wasLeft)
                                previous->left = nullptr;
                            else
                                previous->right = nullptr;
                            actual = nullptr;
                        }
                    }
                }
            }
        }
        
       
        
        // Very funny functions.
        
        void apply 
            (Operator const& op, Traversal const& traversal = inorder) const
        {
            traversal (root, op);
        }
        
        FunTree<T> map (UnaryOperator const& unOp, 
            Traversal const& traversal = inorder, 
            Comparator const& cmp = std::less<T> ()) const
        {
            FunTree<T> newTree;
            this->apply ([&] (T const& element) 
                { newTree.insert (unOp (element), cmp); }, traversal);
            return newTree;
        }
        
        FunTree<T> filter (Predicate const& predicate, 
            Traversal const& traversal = inorder, 
            Comparator const& cmp = std::less<T> ()) const
        {
            FunTree<T> newTree;
            this->apply ([&] (T const& element) 
                { if (predicate (element)) newTree.insert (element, cmp);}, 
                traversal);
            return newTree;
        }
        
        T fold (BinaryOperator const& biOp, T init, 
            Traversal const& traversal = inorder) const
        {
            this->apply ([&] (T const& element) 
                { return init = biOp (init, element); }, traversal);
            return init;
        }
        
        UnaryOperator fun 
            (UnaryOperator const& f, BinaryOperator const& op) const
        {
            return [=] (T const& element) 
                { return op (f (element), root->element); };
        }
        
        // Friend functions.
        friend std::ostream& operator<< 
            (std::ostream& out, Traversal const& traversal)
        {
            defaultTraversal = traversal;
            return out;
        }
        
        friend std::ostream& operator<< 
            (std::ostream& out, FunTree<T> const& tree)
        {
            tree.apply ([&] (T const& element) { out << " " << element; }, 
                defaultTraversal);
            return out;
        }  
};


// Definition for tree traversing functions.
template <class T>
typename FunTree<T>::Traversal FunTree<T>::defaultTraversal = FunTree::inorder;

template <class T>
typename FunTree<T>::Traversal FunTree<T>::preorder = 
    [] (std::shared_ptr<Node> nd, Operator op)
{
    if (nd != nullptr)
    {
        op (nd->element);
        preorder (nd->left, op);
        preorder (nd->right, op);
    }
};

template <class T>
typename FunTree<T>::Traversal FunTree<T>::inorder = 
    [] (std::shared_ptr<Node> nd, Operator op)
{
    if (nd != nullptr)
    {
        inorder (nd->left, op);
        op (nd->element);
        inorder (nd->right, op);
    }
};

template <class T>
typename FunTree<T>::Traversal FunTree<T>::postorder = 
    [] (std::shared_ptr<Node> nd, Operator op)
{
    if (nd != nullptr)
    {
        postorder (nd->left, op);
        postorder (nd->right, op);
        op (nd->element);
    }
};
#endif
