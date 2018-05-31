#pragma once

#include <tuple>
#include <string>

class Renderer
{
	static const std::tuple<int, int> default_dimensions;

public:
	Renderer() = default;
	void init(int& argc, char* argv[], const std::string& window_title) const;
	static void display();
	static void reshape(const int width, const int height);
};

