#include "vta/algorithms.hpp"

#include <climits>
#include <iostream>
#include <random>
#include <type_traits>

constexpr int calculate_switch(int a, bool b) noexcept { return 2 * a + b; }

template <typename... Bools>
constexpr int switch_bools(Bools... bools) noexcept {
	static_assert(sizeof...(bools) < sizeof(int) * CHAR_BIT, "Too many parameters to switch_bools");
	static_assert(vta::are_same_after<std::decay, bool, Bools...>::value, "");
	return vta::add_const(vta::foldl(&calculate_switch))(0, bools...);
}

int main() {
	std::random_device rd;
	std::mt19937 eng{rd()};
	std::uniform_int_distribution<> generate(0, 1);
	bool const a = generate(eng);
	bool const b = generate(eng);
	bool const c = generate(eng);

	switch(switch_bools(a, b, c)) {
		case switch_bools(false, false, false): std::cout << "FFF"; break;
		case switch_bools(false, false, true):  std::cout << "FFT"; break;
		case switch_bools(false, true,  false): std::cout << "FTF"; break;
		case switch_bools(false, true,  true):  std::cout << "FTT"; break;
		case switch_bools(true,  false, false): std::cout << "TFF"; break;
		case switch_bools(true,  false, true):  std::cout << "TFT"; break;
		case switch_bools(true,  true,  false): std::cout << "TTF"; break;
		case switch_bools(true,  true,  true):  std::cout << "TTT"; break;
	}

	std::cout << std::endl;
}
