#include "App/App.hpp"
#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "DEBUG!" << std::endl;
#endif

	sf::RenderWindow window;
	app::App theApp = app::App(window);
	theApp.run();

	std::cout << "EXIT: GOOD" << std::endl;
	return 0;
}

// #include <cmath>
// #include <complex>
// #include <iostream>
// #include <pocketfft-cpp/pocketfft_hdronly.h>
// #include <vector>

// using namespace std;
// using namespace pocketfft;

// template <typename T>
// void crand(vector<complex<T>>& v)
// {
// 	for (auto& i : v)
// 		i = complex<T>(rand() - 0.5, rand() - 0.5);
// }

// int main()
// {
// 	for (size_t len = 1; len < 8192; ++len)
// 	{
// 		shape_t shape { len };
// 		stride_t stridef(shape.size()), strided(shape.size()), stridel(shape.size());
// 		size_t tmpf = sizeof(complex<float>);
// 		for (int i = shape.size() - 1; i >= 0; --i)
// 		{
// 			stridef[i] = tmpf;
// 			tmpf *= shape[i];
// 		}
// 		size_t ndata = 1;
// 		for (size_t i = 0; i < shape.size(); ++i)
// 			ndata *= shape[i];

// 		vector<complex<float>> dataf(ndata);
// 		crand(dataf);

// 		shape_t axes;
// 		for (size_t i = 0; i < shape.size(); ++i)
// 			axes.push_back(i);
// 		vector<complex<float>> resf(dataf.size()/2+1);
// 		r2c(shape, stridef, stridef, axes, FORWARD, dataf.data(), resf.data(), 1.f);
// 	}
// }
