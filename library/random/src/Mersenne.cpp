#include <minecpp/random/Mersenne.h>

namespace minecpp::random {

Mersenne::Mersenne(const std::uint64_t seed) :
    m_engine(seed)
{
}

int Mersenne::next_int()
{
   return static_cast<int>(m_engine());
}

int Mersenne::next_int(const uint32_t bound)
{
   return static_cast<int>(m_engine() % bound);
}

constexpr auto g_double_precision = 0x1000000000;

double Mersenne::next_double()
{
   return static_cast<double>(m_engine() % g_double_precision) / (double) g_double_precision;
}

void Mersenne::reset_seed(const uint64_t seed)
{
   m_engine.seed(seed);
}

}// namespace minecpp::random
