#include <minecpp/random/mersenne.h>

namespace minecpp::random {

Mersenne::Mersenne(const uint64_t seed) : engine(seed) {}

int Mersenne::next_int() { return engine(); }

int Mersenne::next_int(const uint32_t bound) { return engine() % bound; }

constexpr auto DOUBLE_PREC = 0x1000000000;

double Mersenne::next_double() { return static_cast<double>(engine() % DOUBLE_PREC) / (double) DOUBLE_PREC; }

void Mersenne::reset_seed(const uint64_t seed) { engine.seed(seed); }

}// namespace minecpp::random
