#pragma once
#include <string>
#include <vector>
#include <sstream>


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
