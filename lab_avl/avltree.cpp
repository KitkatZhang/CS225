/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp1 = t -> right;
    Node* temp2 = t -> right -> left;
    t ->right = temp2;
    temp1 -> left = t;
    t = temp1;
    t -> left -> height = 1 + max(heightOrNeg1(t -> left -> right), heightOrNeg1(t -> left -> left));
    t -> height = 1 + max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp1 = t -> left;
    Node* temp2 = t -> left -> right;
    t -> left = temp2;
    temp1 -> right = t;
    t = temp1;
    t -> right -> height = 1 + max(heightOrNeg1(t -> right -> right), heightOrNeg1(t -> right -> left));
    t -> height = 1 + max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
     
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t -> right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(heightOrNeg1(subtree -> left) - heightOrNeg1(subtree -> right) > 1){
        if(heightOrNeg1(subtree -> left -> left) - heightOrNeg1(subtree -> left -> right) < 0){
            rotateLeftRight(subtree);
        }else{
            rotateRight(subtree);
        }
    }
    if(heightOrNeg1(subtree -> left) - heightOrNeg1(subtree -> right) < -1){
        if(heightOrNeg1(subtree -> right -> left) - heightOrNeg1(subtree -> right -> right) > 0){
            rotateRightLeft(subtree);
        }else{
            rotateLeft(subtree);
        }
    }
    subtree -> height = 1 + max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right));

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
        subtree = new Node(key, value);
    }else if(key < subtree -> key){
        insert(subtree -> left, key, value);
    }else if(key > subtree -> key){
        insert(subtree -> right, key, value);
    }else{
        subtree -> value = value;
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //Not Node*& temp = subtree -> left;
            Node* temp = subtree -> left;
            while(temp -> right != NULL){
                temp = temp -> right;
            }
            swap(temp, subtree); 
            remove(subtree -> left, key);
        } else {
            /* one-child remove */
            // your code here
            if(subtree -> left == NULL){
                Node* temp = subtree -> right;
                swap(subtree, temp);
                subtree -> right = temp -> right;
                subtree -> left = temp -> left;
                delete temp;
                temp = NULL;
            }else{
                Node* temp = subtree -> left;
                swap(subtree, temp);
                subtree -> right = temp -> right;
                subtree -> left = temp -> left;
                delete temp;
                temp = NULL;
            }
        }
        // your code here
    }
    if(subtree != NULL){
        rebalance(subtree);
    }
}
