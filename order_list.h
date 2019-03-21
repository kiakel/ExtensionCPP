#ifndef _ORDER_LIST_H
#define _ORDER_LIST_H
#include <functional>
using std::greater_equal;
using std::less_equal;
using std::greater;
using std::less;
using std::equal_to;

template<class TTtype>
struct LISTNODE
{
	TTtype data;
	LISTNODE<TTtype>* nextNode;
};

// 默认从大到小排序, 需要TTtype类型提供operator= 和 operator== 和 operator^ , operator>= 或者 operator<= 或者 operator< 或者 operator>
template<class TTtype, class CompareFunc>
class order_list
{
public:
	explicit order_list();
	virtual ~order_list();
	
	// 添加一个元素，并返回链表长度
	unsigned int addNode(const TTtype& data);
	unsigned int addNode(const TTtype* data);

	// 释放一个元素，并返回链表长度
	unsigned int eraseNode(const TTtype& data);
	unsigned int eraseNode(const TTtype* data);

	// 释放某个位置的元素,pos>=1
	unsigned int erasePosNode(unsigned int pos);

	// 释放第一个元素
	unsigned int eraseFrontNode();

	// 释放最后一个元素
	unsigned int eraseBackNode();

	// 链表逆转
	void reverse();

	// 返回第一个元素
	LISTNODE<TTtype>* front() const
	{
		return m_headNode->nextNode;
	}

	// 返回最后一个元素
	LISTNODE<TTtype>* back() const
	{
		return m_tailNode;
	}

	// 释放整个链表
	void destory();

	void setFixSize(unsigned int length)
	{
		m_fixSize = length;
	}

private:
	 // 创建一个LISTNODE<TTtype>节点
	LISTNODE<TTtype>* createNode(const TTtype& data)
	{
		LISTNODE<TTtype>* node = new LISTNODE<TTtype>();
		node->data = data;
		node->nextNode = nullptr;
		return node;
	}

	LISTNODE<TTtype>* createNode(const TTtype* data)
	{
		LISTNODE<TTtype>* node = new LISTNODE<TTtype>();
		node->data = *data;
		node->nextNode = nullptr;
		return node;
	}

	void insertNode(LISTNODE<TTtype>* node);
private:
	LISTNODE<TTtype>* m_headNode;
	LISTNODE<TTtype>* m_tailNode;
	unsigned int m_length; //!< 链表长度
	unsigned int m_fixSize; //!< 记录setFixSize()
	CompareFunc m_compare;
};

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
order_list<TTtype, CompareFunc>::order_list()
:m_headNode(new LISTNODE<TTtype>())
, m_tailNode(nullptr)
{
	m_headNode->nextNode = nullptr;
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
order_list<TTtype, CompareFunc>::~order_list()
{
	if (m_headNode->nextNode)
	{
		this->destory();
	}
	delete m_headNode; m_headNode = nullptr; 

}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
unsigned int order_list<TTtype, CompareFunc>::addNode(const TTtype& data)
{
	m_length++;
	LISTNODE<TTtype>* node = createNode(data);

	if (m_headNode->nextNode)
	{
		insertNode(node);
	}
	else
	{
		m_headNode->nextNode = node;
		m_tailNode = node;
	}
	return m_length;
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
unsigned int order_list<TTtype, CompareFunc>::addNode(const TTtype* data)
{
	return addNode(*data);
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
void order_list<TTtype, CompareFunc>::insertNode(LISTNODE<TTtype>* node)
{
	LISTNODE<TTtype>* travelNode = m_headNode->nextNode;
	
	// 是否可以直接插入到尾节点
	if (m_compare(m_tailNode->data, node->data))
	{
		m_tailNode->nextNode = node;
		m_tailNode = node;
		if (m_length > m_fixSize)
		{
			eraseBackNode();
		}
		return;
	}

	LISTNODE<TTtype>*  preNode = m_headNode;
	while (preNode->nextNode)
	{
		if (m_compare(node->data, preNode->nextNode->data))
		{
			break;
		}
		preNode = preNode->nextNode;
	}
	LISTNODE<TTtype>* tmpNode = preNode->nextNode;
	preNode->nextNode = node;
	node->nextNode = tmpNode;
	if (m_length > m_fixSize)
	{
		eraseBackNode();
	}
}


template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
unsigned int order_list<TTtype, CompareFunc>::eraseNode(const TTtype& data)
{
	LISTNODE<TTtype>* preNode = m_headNode;

	while (preNode->nextNode)
	{
		if (!(preNode->nextNode->data ^ data))
		{
			m_length--;
			if (!(preNode->nextNode ^ m_tailNode))
			{
				if (m_length == 0)
				{
					m_tailNode = nullptr;
				}
				else
				{
					m_tailNode = preNode;
				}
			}
			LISTNODE<TTtype>* equalNode = preNode->nextNode;
			preNode->nextNode = equalNode->nextNode;
			delete equalNode; equalNode = nullptr;
		}
		if (preNode->nextNode->data ^ data)
		{
			break;
		}
	}
	return m_length;
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
unsigned int order_list<TTtype, CompareFunc>::eraseNode(const TTtype* data)
{
	return eraseNode(*data);
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
unsigned int order_list<TTtype, CompareFunc>::erasePosNode(unsigned int pos)
{
	unsigned int index = 0;
	LISTNODE<TTtype>* node = m_headNode;
	while (node->nextNode)
	{
		if (index++ == pos - 1)
		{
			break;
		}
		node = node->nextNode;
	}

	if (m_length == pos)
	{
		if ((m_length - 1) == 0)
		{
			m_tailNode = nullptr;
		}
		else
		{
			m_tailNode = node;
		}
	}
	
	m_length--;
	LISTNODE<TTtype>* deleteNode = node->nextNode;
	
	node->nextNode = deleteNode->nextNode;
	delete deleteNode;
	deleteNode = nullptr;
	
	return m_length;
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
unsigned int order_list<TTtype, CompareFunc>::eraseFrontNode()
{
	if (m_length == 1)
	{
		m_tailNode = nullptr;
	}
	LISTNODE<TTtype>* firstNode = m_headNode->nextNode;
	m_headNode->nextNode = firstNode->nextNode;
	delete firstNode;
	firstNode = nullptr;
	m_length--;
	return m_length;
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
unsigned int order_list<TTtype, CompareFunc>::eraseBackNode()
{
	return erasePosNode(m_length);
}


template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
void order_list<TTtype, CompareFunc>::destory()
{
	while (m_length > 0)
	{
		eraseFrontNode();
	}
}

template<class TTtype, class CompareFunc/*=std::greater_equal<TTtype>*/>
void order_list<TTtype, CompareFunc>::reverse()
{
	if (m_length < 2)
		return;

	LISTNODE<TTtype>* tailNode = m_headNode->nextNode;
	LISTNODE<TTtype>* firstNode = tailNode->nextNode;
	LISTNODE<TTtype>* tmpNode = firstNode->nextNode;

	while (tailNode->nextNode)
	{
		m_headNode->nextNode = firstNode;
		firstNode->nextNode = tailNode;
		while (tailNode->nextNode != m_headNode->nextNode)
		{
			tailNode = tailNode->nextNode;
		}
		tailNode->nextNode = tmpNode;
		if (tmpNode == nullptr)
		{
			m_tailNode = tailNode;
			break;
		}
		tmpNode = tmpNode->nextNode;
		firstNode = tailNode->nextNode;
		tailNode = m_headNode->nextNode;
	}
}

#endif // _ORDER_LIST_H
