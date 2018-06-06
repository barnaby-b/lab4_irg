#include <glm/detail/type_vec2.hpp>

namespace frac
{
	typedef struct
	{
		double re;
		double im;
	} complex;

	int divergence_test(complex c, int limit)
	{
		complex z;
		z.re = 0;
		z.im = 0;

		for(auto i = 0u; i <= limit; ++i)
		{
			const auto next_re = z.re*z.re - z.im * z.im + c.re;
			const auto next_im = 2 * z.re*z.im + c.im;

			z.re = next_re;
			z.im = next_im;

			const auto mod_sq = z.re*z.re + z.im*z.im;
			if(mod_sq > 4)
			{
				return i;
			}
		}

		return -1;
	}

	glm::vec2 screen_to_complex(int x, int y)
	{
		static auto xmin = 0;
		static auto xmax = 480;

		static auto ymin = 0;
		static auto ymax = 640;

		static auto umin = -2.0;
		static auto umax = 1.0;

		static auto vmin = -1.2;
		static auto vmax = 1.2;

		return
		{
			(x - xmin) / static_cast<double>(xmax - xmin) * (umax - umin) + umin,
			(y - ymin) / static_cast<double>(ymax - ymin) * (vmax - vmin) + vmin
		};
	}
}
