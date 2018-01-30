//
// Created by wenshao on 18-1-10.
//

#include <iostream>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode* invertTree(struct TreeNode* root) {
    if(root==NULL) return NULL;
    struct TreeNode* tmp=root->left;
    root->left=invertTree(root->right);
    root->right=invertTree(tmp);
    return root;

}

int main(){
    return 0;
}