#include "./search_algorithm.h"

int maxChildSerialize(const vector<int>& serialize)
{
	vector<int> depth(serialize.size(), 1);
	for (int index = 1; index < serialize.size(); ++index)
	{
		int littleCount = 1; // 子序列最大深度
		for (int innerIndex = 0; innerIndex < index; ++innerIndex)
		{
			if (serialize.at(innerIndex) < serialize.at(index))
			{
				littleCount = depth.at(innerIndex) + 1;
			}
			else
			{
				littleCount = depth.at(innerIndex);
			}
		}
		if (littleCount > depth.at(index))
		{
			depth[index] = littleCount;
		}
	}
	return depth.at(serialize.size() - 1);
}