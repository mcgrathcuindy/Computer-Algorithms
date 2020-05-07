/*
NAME: Christopher McGrath
DATE: 2/10/20
DESC: CSCI 430 HW3
*/
//C++ program to Implement AVL Tree
//Balance Factor = Height of left subtree-Height of right subtree
//Height of null tree = 0
//Height of leaf nodes =1

#include<bits/stdc++.h> 
using namespace std;
 
/*
 * Node Declaration
 */
struct avl_node
{
    int data;
    struct avl_node *left;
    struct avl_node *right;
}*root;
 
/*
 * Class Declaration
 */
class avlTree
{
    public:
        int height(avl_node *);
        int diff(avl_node *);
        avl_node *rr_imbalance(avl_node *);
        avl_node *ll_imbalance(avl_node *);
        avl_node *lr_imbalance(avl_node *);
        avl_node *rl_imbalance(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert(avl_node *, int );
        void display(avl_node *, int);
        void inorder(avl_node *);
        void preorder(avl_node *);
        void postorder(avl_node *);
        avlTree()
        {
            root=NULL;     
        }
};
 
/*
 * Main Contains Menu
 */
int main()
{
    int choice, item, n, i;
    avlTree avl;
    ifstream file; 
    // opening file "input.txt" 
    // in (read) mode 
    // ios::in Open for input operations. 
    file.open("input.txt",ios::in); 
    // If no file is created, then 
    // show the error message. 
    if(!file) 
    { 
        cout<<"Error in creating file!!!"; 
        return 0; 
    } 
    cout<<"File opened successfully."; 
    file>>n;

    for(i = 0; i < n; i++)
    {
        file>>item;
        root = avl.insert(root, item);
    }
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        cout<<"3.InOrder traversal"<<endl;
        cout<<"4.PreOrder traversal"<<endl;
        cout<<"5.PostOrder traversal"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout << "Enter a value to insert" << endl;
                cin >> item;
                avl.insert(root,item);
                break;
            case 2:
                if (root == NULL)
                {
                    cout<<"Tree is Empty"<<endl;
                    continue;
                }
                cout<<"Balanced AVL Tree:"<<endl;
                avl.display(root, 1);
                break;
            case 3:
                if(root == NULL)
                {
                    cout << "Tree is Empty"<<endl;
                    continue;
                }
                cout << "Inorder Traversal: "<< endl;
                avl.inorder(root);
                break;
            case 4:
                if(root == NULL)
                {
                    cout << "Tree is Empty"<<endl;
                    continue;
                }
                cout << "Preorder Traversal: "<< endl;
                avl.preorder(root);
                break;
            case 5:
                if(root == NULL)
                {
                    cout << "Tree is Empty"<<endl;
                    continue;
                }
                cout << "Postorder Traversal: "<< endl;
                avl.postorder(root);
                break;
            case 6:
                file.close();
                exit(1);    
                break;
            default:
                cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
 
//recursive function to find the height of AVL tree
// leaf node height is 1, null left/right child height is 0 
int avlTree::height(avl_node *temp)
{
    if(temp == NULL)
        return 0;
    else
    {
        int lHeight = height(temp -> left);
        int rHeight = height(temp -> right);
        if(lHeight > rHeight)
            return(lHeight +1);
        else
            return(rHeight +1);
    }
}
 
//Calculate and return the balance factor
int avlTree::diff(avl_node *temp)
{
    int difference = height(temp->left) - height(temp -> right);
    return difference;
}
 
// Case: Right subtree of right child
avl_node *avlTree::rr_imbalance(avl_node *parent)
{
    avl_node * temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// Case: Left subtree of left child 
avl_node *avlTree::ll_imbalance(avl_node *parent)
{
    avl_node *temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
} 
 
//Right subtree of Left child
avl_node *avlTree::lr_imbalance(avl_node *parent)
{
    avl_node *temp = parent->left;
    parent->left = rr_imbalance(temp);
    return ll_imbalance(parent);
}
 
//Left subtree of Right child
avl_node *avlTree::rl_imbalance(avl_node *parent)
{   
    avl_node *temp = parent->right;
    parent->right = ll_imbalance(temp);
    return rr_imbalance(parent);
}
 
/*
Balancing AVL Tree
*/
avl_node *avlTree::balance(avl_node *temp)
{
    //if (bf of temp>1) and (bf of temp->left>0) => Case LL imbalance
    if(diff(temp)>1 && diff(temp->left)>0)
        temp = ll_imbalance(temp);
    //if (bf of temp>1) and (bf of temp->left<0) => Case LR imbalance
    if(diff(temp)>1 && diff(temp->left) < 0)
        temp = lr_imbalance(temp);
    //if (bf of temp<-1) and (bf of temp->right>0) => Case RL imbalance
    if(diff(temp)<-1 && diff(temp->right) > 0)
        temp = rl_imbalance(temp);
    //if (bf of temp<-1) and (bf of temp->right<0) => Case RR imbalance
    if(diff(temp)<-1&&diff(temp->right) < 0)
        temp = rr_imbalance(temp);
    return temp;
}
 
/*
 * Insert Element into the tree
 */
avl_node *avlTree::insert(avl_node *root, int value)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}
 
/*
 * Display AVL Tree
 */

void avlTree::display(avl_node *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

/*
 * Inorder Traversal of AVL Tree
 */
void avlTree::inorder(avl_node *tree)
{
    if(tree != NULL)
    {
        inorder(tree -> left);
        cout << tree->data << " ";
        inorder(tree -> right);
    }
}
/*
 * Preorder Traversal of AVL Tree
 */
void avlTree::preorder(avl_node *tree)
{
    if(tree != NULL)
    {
        cout << tree->data << " ";
        preorder(tree -> left);
        preorder(tree -> right);
    }
} 
/*
 * Postorder Traversal of AVL Tree
 */
void avlTree::postorder(avl_node *tree)
{
    if(tree != NULL)
    {
        postorder(tree -> left);
        postorder(tree -> right);
        cout << tree->data << " ";
    }
}
