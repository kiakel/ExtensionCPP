#include "./struct_tree.h"
#include <iostream>
using namespace std;
DictTree::DictTree()
	: m_root(new CharNode())
	, m_index(0)
{
	m_root->count = 0;
	m_root->data = ' ';
	m_root->nextNode.clear();
}

CharNode* DictTree::searchStringNode(const string& text,bool& isFind)
{
	unsigned int index = 0;
	CharNode* node = m_root;

	while (index<text.length())
	{
		CharNode* existsNode = NULL;
		// 节点的子节点是否存在某个字符
		for (auto iter=node->nextNode.begin();iter!=node->nextNode.end();++iter)
		{
			if (!(((*iter)->data) ^  (text.at(index)))) // 成功匹配字符
			{
				existsNode = (*iter);
			}
		}
		
		if (!existsNode)
		{
			isFind = false;
			break;
		}
		else
		{
			isFind = true;
			node = existsNode;
		}
		index++;
	}
	m_index = index; 
	
	return node;
}

int DictTree::countString(const string& text)
{
	bool isFind = false;
	CharNode* node = searchStringNode(text, isFind);
	if (isFind)
	{
		return node->count;
	}
	return 0;
}

void DictTree::insertNode(const string& text)
{
	bool isFind = false;
	CharNode* startNode = searchStringNode(text,isFind);
	if (isFind)
	{
		startNode->count++;
	}
	else
	{
		string subText = text.substr(m_index);
		CharNode* childNode = NULL;
		for (int strIndex=0;strIndex<subText.length();++strIndex)
		{
			childNode = createNode(subText[strIndex]);
			startNode->nextNode.insert(childNode);
			startNode = childNode;
		}
		childNode->count++;
	}
}

const vector<string> DictTree::topK(const int top)
{
	string text{};
	m_topK.setFixSize(top);
	m_tailK.setFixSize(top);

	travelNodes(m_root, text);
	vector<string> result;
	LISTNODE<CountNode>* first = m_topK.front();
	while (first)
	{
		result.push_back(first->data.text);
		first = first->nextNode;
	}
	return result;
}

const vector<string> DictTree::tailK(const int tail)
{
	m_topK.destory();
	m_tailK.destory();
	topK(tail);
	vector<string> result;
	LISTNODE<CountNode>* first = m_tailK.front();
	while (first)
	{
		result.push_back(first->data.text);
		first = first->nextNode;
	}
	return result;
}

CharNode* DictTree::createNode(char ch)
{
	CharNode* node = new CharNode();
	node->data = ch;
	node->count = 0;
	node->nextNode.clear();
	return node;
}

void DictTree::travelNodes(CharNode*node, string& preText)
{
	
	for (auto iter=node->nextNode.cbegin();iter!=node->nextNode.cend();++iter) // 
	{
		CharNode* tmpNode = (*iter);
		preText += tmpNode->data;
		
		if (tmpNode->count>0)
		{
			cout <<"preText: "<< preText << endl;
			m_topK.addNode(new CountNode(preText, tmpNode->count));

			m_tailK.addNode(new CountNode(preText, tmpNode->count));
		}

		travelNodes(tmpNode, preText);
	} // for 

	if (preText.size()>=1)
	{
		preText.erase(preText.size() - 1);
	}
}

