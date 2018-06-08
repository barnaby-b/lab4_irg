#pragma once
#include <string>
#include <vector>
#include <sstream>

//C program to generate random numbers according to given frequency distribution
#include <cstdlib>

inline int find_ceil(const int arr[], const int r, int l, int h)
{
	while (l < h)
	{
		const auto mid = l + ((h - l) >> 1);
		(r > arr[mid]) ? (l = mid + 1) : (h = mid);
	}
	return (arr[l] >= r) ? l : -1;
}

// The main function that returns a random number from arr[] according to
// distribution array defined by freq[]. n is size of arrays.
inline int my_rand(std::vector<int> arr, std::vector<int> freq, const int n)
{
	// Create and fill prefix array
	auto *prefix = new int[n];
	prefix[0] = freq[0];
	for (auto i = 1; i < n; ++i)
		prefix[i] = prefix[i - 1] + freq[i];

	// prefix[n-1] is sum of all frequencies. Generate a random number
	// with value from 1 to this sum
	const auto r = (rand() % prefix[n - 1]) + 1;

	// Find index of ceiling of r in prefix arrat
	const auto indexc = find_ceil(prefix, r, 0, n - 1);
	delete[] prefix;
	return arr[indexc];
}

inline std::vector<double> parse_nums(const std::string& line)
{
	std::stringstream ss(line);
	std::vector<double> res{};
	auto a = 0.0;
	while (ss >> a)
	{
		res.push_back(a);
	}

	return res;
}

inline std::string strip_comments(const std::string& line)
{
	const auto com_ind = line.find('#');

	if (com_ind == std::string::npos)
	{
		return line;
	}

	return line.substr(0, com_ind);
}

inline int parse_int(const std::string& line)
{
	std::stringstream ss(line);

	auto res = 0;
	ss >> res;

	return res;
}
