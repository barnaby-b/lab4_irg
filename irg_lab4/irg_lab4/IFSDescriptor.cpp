#include "IFSDescriptor.h"
#include "parser_helper.hpp"
#include <string>

IfsDescriptor IfsDescriptor::from_stream(std::istream& is)
{
	std::string points_number_str;
	std::getline(is, points_number_str);
	const auto points_number = parse_int(strip_comments(points_number_str));

	std::string limit_str;
	std::getline(is, limit_str);
	const auto limit = parse_int(strip_comments(limit_str));

	std::string etas_1_2_str;
	std::getline(is, etas_1_2_str);
	const auto etas_1_2 = parse_nums(strip_comments(etas_1_2_str));

	std::string etas_3_4_str;
	std::getline(is, etas_3_4_str);
	const auto etas_3_4 = parse_nums(strip_comments(etas_3_4_str));

	ifs_table result;
	
	std::string frac_def_line;
	while(std::getline(is, frac_def_line))
	{
		if(frac_def_line.find('#') == 0)
		{
			continue;
		}

		result.push_back(parse_nums(strip_comments(frac_def_line)));
	}

	return IfsDescriptor(points_number, limit, { etas_1_2[0], etas_1_2[1], etas_3_4[0], etas_3_4[1] }, result);
}

int IfsDescriptor::points_number() const
{
	return points_number_;
}

int IfsDescriptor::limit() const
{
	return limit_;
}

const std::tuple<double, double, double, double>& IfsDescriptor::etas() const
{
	return etas_;
}

const IfsDescriptor::ifs_table& IfsDescriptor::table() const
{
	return table_;
}

const std::vector<double>& IfsDescriptor::weights() const
{
	return weights_;
}

IfsDescriptor::IfsDescriptor(IfsDescriptor&& other) noexcept: points_number_(other.points_number_),
                                                              limit_(other.limit_),
                                                              etas_(std::move(other.etas_)),
                                                              table_(std::move(other.table_))
{
}

IfsDescriptor& IfsDescriptor::operator=(const IfsDescriptor& other)
{
	if (this == &other)
		return *this;
	points_number_ = other.points_number_;
	limit_ = other.limit_;
	etas_ = other.etas_;
	table_ = other.table_;
	return *this;
}

IfsDescriptor& IfsDescriptor::operator=(IfsDescriptor&& other) noexcept
{
	if (this == &other)
		return *this;
	points_number_ = other.points_number_;
	limit_ = other.limit_;
	etas_ = std::move(other.etas_);
	table_ = std::move(other.table_);
	return *this;
}
