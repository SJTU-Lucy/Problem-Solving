#include "Tree.h"
#include<iostream>
using namespace std;


// ==================== k-d tree ======================
kdNode::kdNode(int a,int b,bool flag) {
	key[0] = a;
	key[1] = b;
	deleted = flag;
}

kdTree::kdTree(){
	root = new kdNode(0, 0, true);
}

void kdTree::insert(kdNode* root, int arr[], int dim){
	if (root->deleted)
	{
		root->key[0] = arr[0];
		root->key[1] = arr[1];
		root->deleted = false;
		return;
	}

	if (root->key[0] == arr[0] && root->key[1] == arr[1]) return;
	if (arr[dim] < root->key[dim])
	{
		if (root->left == nullptr) 
			root->left = new kdNode(0, 0, true);
		insert(root->left, arr, (dim + 1) % 2);
	}
	else
	{
		if (root->right == nullptr)
			root->right = new kdNode(0, 0, true);
		insert(root->right, arr, (dim + 1) % 2);
	}
}

kdNode* kdTree::search(kdNode* root, int arr[], int dim){
	if (root == nullptr) return nullptr;
	if (root->deleted) return nullptr;
	if (root->key[0] == arr[0] && root->key[1] == arr[1]) return root;
	if (arr[dim] < root->key[dim]) return search(root->left, arr, (dim + 1) % 2);
	else return search(root->right, arr, (dim + 1) % 2);
}

void kdTree::remove(kdNode* root, int arr[], int dim){
	kdNode* target = search(root, arr, dim);
	if (target == nullptr) return;
	else helper(target, target->layer);
}

void kdTree::helper(kdNode* root, int dim)
{
	if (!root->left && !root->right)
	{
		root->deleted = true;
		return;
	}
	kdNode* sub = nullptr;
	if (root->right) sub = findMin(root, dim, dim);
	else if (root->left) sub = findMax(root, dim, dim);
	root->key[0] = sub->key[0];
	root->key[1] = sub->key[1];
	helper(sub, sub->layer);
	
}

kdNode* kdTree::findMin(kdNode* root, int dimCmp, int dim){
	if (root == nullptr) return nullptr;
	if (root->deleted) return nullptr;
	kdNode* min = findMin(root->left, dimCmp, (dim + 1) % 2);
	if (dimCmp != dim)
	{
		kdNode* rightMin = findMin(root->right, dimCmp, (dim + 1) % 2);
		if (min && rightMin)
			min = min->key[dimCmp] < rightMin->key[dimCmp] ? min : rightMin;
		else if (rightMin) min = rightMin;
	}
	if (min == nullptr) return root;
	return root->key[dimCmp] < min->key[dimCmp] ? root : min;
}

kdNode* kdTree::findMax(kdNode* root, int dimCmp, int dim) {
	if (root == nullptr) return nullptr;
	if (root->deleted) return nullptr;
	if (!root->left && !root->right) return root;
	kdNode* max = findMax(root->left, dimCmp, (dim + 1) % 2);
	if (dimCmp != dim)
	{
		kdNode* rightMax = findMax(root->right, dimCmp, (dim + 1) % 2);
		if (max && rightMax)
			max = max->key[dimCmp] > rightMax->key[dimCmp] ? max : rightMax;
		else if (rightMax) max = rightMax;
	}
	if (max == nullptr) return root;
	return root->key[dimCmp] > max->key[dimCmp] ? root : max;
}

vector<struct kdNode*> kdTree::rangeSearch(kdNode* root, int dim, int lower_bound[], int upper_bound[]){
	vector<kdNode*> res;
	traverse(res, root, 0, lower_bound, upper_bound);
	return res;						 
}

void kdTree::traverse(vector<kdNode*>& res, kdNode* root, int dim, int lower_bound[], int upper_bound[]){
	if (root == nullptr) return;
	if (root->deleted) return;
	if (root->key[0] >= lower_bound[0] && root->key[0] <= upper_bound[0]
		&& root->key[1] >= lower_bound[1] && root->key[1] <= upper_bound[1])
	{
		res.push_back(root);
	}
	traverse(res, root->left, (dim + 1) % 2, lower_bound, upper_bound);
	traverse(res, root->right, (dim + 1) % 2, lower_bound, upper_bound);
}


// ==================== trie (prefix tree) ======================
TrieNode::TrieNode() {
	for (int i = 0; i < 26; ++i)
		next['a' + i] = nullptr;
}

Trie::Trie() {
	root = new TrieNode();
	root->flag = false;
}

void Trie::insert(string word) {
	auto tmp = this->root;
	for (int i = 0; i < word.size(); ++i)
	{
		char t = word[i];
		if (tmp->next[t] == nullptr)
		{
			tmp->next[t] = new TrieNode();
			tmp = tmp->next[t];
			if (i == word.size() - 1) tmp->flag = true;
		}
		else
		{
			tmp = tmp->next[t];
			if (i == word.size() - 1) tmp->flag = true;
		}
	}
}


bool Trie::search(string word) {
	auto tmp = this->root;
	for (int i = 0; i < word.size(); ++i)
	{
		char t = word[i];
		if (tmp->next[t] == nullptr) return false;
		else tmp = tmp->next[t];
	}
	if (tmp->flag) return true;
	else return false;
}


bool Trie::startsWith(string prefix) {
	auto tmp = this->root;
	
	for (int i = 0; i < prefix.size(); ++i)
	{
		char t = prefix[i];
		if (tmp->next[t] == nullptr) return false;
		else tmp = tmp->next[t];
	}
	return true;
}
