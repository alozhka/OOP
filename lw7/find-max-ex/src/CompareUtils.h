#pragma once
#include <functional>
#include <vector>

namespace CompareUtils
{
template <typename T, typename Less>
bool FindMax(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	T temp = arr[0];
	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (less(temp, arr[i]))
		{
			temp = arr[i];
		}
	}

	maxValue = temp;
	return true;
}
} // namespace CompareUtils
