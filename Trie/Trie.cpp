#include<iostream>
#include<vector>
using namespace std;

struct TrieNode
{
	bool isEnd = false;
	char record;
	int childCount = 0;
	vector<TrieNode*> children = vector<TrieNode*>(26,nullptr);
};

class Trie
{
public:
	TrieNode* root;
	vector<string> words;
	Trie() 
	{
		root = new TrieNode;
	}

	void check()
	{
		words.clear();
		traverse(root, "");
		for (int i = 0; i < words.size(); ++i)
		{
			cout << words[i] << endl;
		}
	}

	void traverse(TrieNode* tmp,string stimu)
	{
		if (tmp->childCount == 0)
		{
			if (tmp->isEnd) words.push_back(stimu);
			return;
		}
		if (tmp->isEnd) words.push_back(stimu);
		for (int i = 0; i < 26; ++i)
		{
			if (tmp->children[i] == nullptr) continue;
			else
			{
				stimu.push_back('a' + i);
				traverse(tmp->children[i], stimu);
				stimu.pop_back();
			}
		}

	}

	void Insert(string target)
	{
		auto tmp = root;
		for (int i=0;i<target.size();++i)
		{
			char t = target[i];
			if (tmp->childCount==0||tmp->children[t - 'a'] == nullptr)
			{
				tmp->childCount++;
				tmp->children[t - 'a'] = new TrieNode;

				tmp = tmp->children[t - 'a'];
				tmp->record = t;
				if (i == target.size()-1) tmp->isEnd = true;
			}
			else
			{
				tmp = tmp->children[t - 'a'];
				tmp->record = t;
				if (i == target.size()-1) tmp->isEnd = true;
			}
		}
	}

	void Delete(string target) 
	{
		auto tmp = root;
		traceBack(root, target, 0);
	}

	void traceBack(TrieNode* tmp, string target, int cur)
	{
		//cout << target[cur];
		//如果要删的是下标为n的，意思是已经搜到这个单词了，直接开删
		if (cur == target.size())
		{
			if (tmp->childCount == 0)
			{
				tmp->childCount--;
			}
			else tmp->isEnd = false;
			return;
		}
		//如果遇到没有子节点or无对应子节点，说明该单词不存在
		if (tmp->childCount == 0 || tmp->children[target[cur] - 'a'] == nullptr)
		{
			return;
		}
		auto next = tmp->children[target[cur] - 'a'];
		traceBack(next, target, cur + 1);
		//如果发现子节点被删掉了
		if (tmp->children[target[cur] - 'a']->childCount == -1)
		{
			delete tmp->children[target[cur] - 'a'];
			tmp->children[target[cur] - 'a'] = nullptr;
			tmp->childCount -= 1;
			if (tmp->childCount == 0 && tmp->isEnd == false)
			{
				tmp->childCount--;
			}
		}
	}
	bool Exist(string target) 
	{
		auto tmp = root;
		for (int i = 0; i < target.size(); ++i)
		{
			char t = target[i];
			if (tmp->childCount == 0 || tmp->children[t - 'a'] == nullptr)
			{
				return false;
			}
			else
			{
				tmp = tmp->children[t - 'a'];
			}
		}
		if (tmp->isEnd) return true;
		else return false;
	}
};

int main()
{
	Trie Test;
	Test.Insert("hello");
	Test.Insert("world");
	Test.Insert("hell");
	cout << "first check:" << endl;
	Test.check();
	Test.Delete("hello");
	Test.Delete("hell");
	Test.Delete("hel");
	cout << "second check:" << endl;
	Test.check();
	if (Test.Exist("hello")) cout << "Exist!" << endl;
	else cout << "not Exist!" << endl;
	return 0;
}