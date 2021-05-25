#include "h1_d0.hpp"
#include "h2_d0.hpp"
#include "h3_d0.hpp"
#include "h4_d0.hpp"
#include "h5_d0.hpp"


int main() {
	int a = h1d0_ns::return11();
	int b = h2d0_ns::return12();
	int c = h3d0_ns::return13();
	int d = h4d0_ns::return14();
	int e = h5d0_ns::return15();

	return a + b + c + d + e;
}