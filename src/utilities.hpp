#pragma once

namespace ga {
template <unsigned int N> struct CALCULATE_MAX_VALUE {
  static constexpr std::uint64_t value =
      2 * CALCULATE_MAX_VALUE<N - 1>::value;
};

template <> struct CALCULATE_MAX_VALUE<0> {
  static constexpr std::uint64_t value = 1;
};

std::random_device rand_dev;
std::mt19937_64 rng(rand_dev());

template <typename T> T uniform(T min, T max) {
  static std::uniform_real_distribution<> probability(0, 1);
  if (min >= max) {
    std::source_location location = std::source_location::current();
    std::string errorMessage =
        "Error: " + std::string(location.function_name()) + ". min<max.";
    throw std::invalid_argument(errorMessage);
  }
  return min + probability(rng) * (max - min);
}

template <unsigned int N> class Randomize {
  static_assert(N > 0 && N <= 64,
                "Template parameter N must be in interval [1,64].");

public:
  static constexpr std::uint64_t MAX_VALUE = ga::CALCULATE_MAX_VALUE<N>::value - 1;

  static std::uint64_t generate() {
    static std::uniform_int_distribution<std::uint64_t> uniformDistribution(
        0, MAX_VALUE);
    return uniformDistribution(rng);
  }
};

std::string Uint64ToString(const std::uint64_t value)
{
    std::bitset<sizeof(std::uint64_t)*8> bits(value);
    return bits.to_string();
}

std::uint64_t StringToUint64(const std::string& s)
{
    std::uint64_t value = 0;
    std::uint64_t x = 0;
    std::for_each(s.begin(),s.end(),[&x](const char &c) {
	    x = (x<<1)+(c-'0');
	    });
    std::memcpy(&value,&x,sizeof(uint64_t));
    return value;
}

} // namespace ga
