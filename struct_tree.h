#ifndef _STRUCT_TREE_H
#define _STRUCT_TREE_H
#include <set>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "./order_list.h"
using std::set;
using std::string;
using std::list;
using std::vector;
// AVL树


// 红黑树

// 字典树
struct CountNode
{
	string text;
	unsigned int count;
	CountNode() :text(), count(0) {}
	CountNode(string str, unsigned int ct) :text(str), count(ct) {}
	CountNode& operator=(const CountNode& rValue)
	{
		this->text.assign(rValue.text);
		this->count = rValue.count;
		return *this;
	}
	bool operator^(const CountNode& rValue)const
	{
		return this->count ^ rValue.count;
	}

	bool operator>(const CountNode& rValue)const
	{
		return this->count > rValue.count;
	}

	bool operator==(const CountNode& rValue)const
	{
		return !operator^(rValue);
	}

	bool operator<(const CountNode& rValue)const
	{
		return this->count < rValue.count;
	}

	bool operator>=(const CountNode& rValue)const
	{
		return operator>(rValue) || operator==(rValue);
	}

	bool operator<=(const CountNode& rValue)const
	{
		return operator<(rValue) || operator==(rValue);
	}
};
struct CharNode
{
	char data; // 当前节点的字符
	unsigned int count; // 当前节点到根节点组成字符串在文章中出现的次数
	set<CharNode*> nextNode; // 当前节点子节点
};

class DictTree
{
public:
	explicit DictTree();

	// 统计字符串在字典树中出现的频率
	int countString(const string& text);

	// 向字典树中加入字符串text
	void insertNode(const string& text);

	// top K问题,出现最多的字符串
	const vector<string> topK(const int top);

	// tail K问题,出现最少的字符串
	const vector<string> tailK(const int tail);

private:
	/**
	 *  字符串的字符在字典树中最后出现的节点位置和整个字符串是否在字典树中存在
	 * 假设"hello"字符串已经在字典树中，查找"he"，函数返回"hello"路径中的'e'节点，isFind是true；
	 * 继续查找"head",函数返回"hello"路径中的'e'节点(表示共有"he"路径)，isFind是false；
	 */
	CharNode* searchStringNode(const string& text, bool& isFind);

	CharNode* createNode(char ch);

	// 某个节点的下一层节点
	void travelNodes(CharNode*node,  string& preText);

	// 从后向前插入数据
	void insertHead(unsigned int value, const string& text);

	// 从前向后插入数据
	void insertBack(unsigned int value, const string& text);
private:
	CharNode* m_root; //!< 字典树根节点
	unsigned int m_index; //!< 被搜索字符串的第几个字符不在字典树路径中
	unsigned int m_ttLength; //!< 
	order_list<CountNode,std::greater_equal<CountNode>> m_topK;
	order_list<CountNode, std::less_equal<CountNode>> m_tailK;
};


#endif