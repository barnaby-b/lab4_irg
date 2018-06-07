#pragma once
#include <tuple>
#include <vector>
#include <array>
#include <ostream>

class IfsDescriptor
{
	int points_number_;
	int limit_;
	std::tuple<double, double, double, double> etas_;
	typedef std::vector<std::vector<double>> ifs_table;
	ifs_table table_;
	std::vector<double> weights_;

public:

	IfsDescriptor(const int points_number, const int limit, std::tuple<double, double, double, double> etas,
		ifs_table arrays)
		: points_number_(points_number),
		  limit_(limit),
		  etas_(std::move(etas)),
		  table_(std::move(arrays))
	{
		for(auto el : table_)
		{
			if (!el.empty()) {
				weights_.push_back(el[6]);
			}
		}
	}


	static IfsDescriptor from_stream(std::istream& is);
	int points_number() const;
	int limit() const;
	const std::tuple<double, double, double, double>& etas() const;
	const ifs_table& table() const;
	const std::vector<double>& weights() const;
	IfsDescriptor(const IfsDescriptor& other) = default;
	IfsDescriptor(IfsDescriptor&& other) noexcept;
	IfsDescriptor& operator=(const IfsDescriptor& other);
	IfsDescriptor& operator=(IfsDescriptor&& other) noexcept;
};


