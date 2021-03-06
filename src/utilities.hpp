#pragma once

namespace ga {
template <unsigned int N> struct CALCULATE_MAX_VALUE {
  static constexpr std::uint64_t value = 2 * CALCULATE_MAX_VALUE<N - 1>::value;
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
  return static_cast<T>(min + probability(rng) * (max - min));
}

template <unsigned int N> class Randomize {
  static_assert(N > 0 && N <= 64,
                "Template parameter N must be in interval [1,64].");

public:
  static constexpr std::uint64_t MAX_VALUE =
      ga::CALCULATE_MAX_VALUE<N>::value - 1;

  static std::uint64_t generate() {
    static std::uniform_int_distribution<std::uint64_t> uniformDistribution(
        0, MAX_VALUE);
    return uniformDistribution(rng);
  }
};

template <typename T> std::string UintToString(const std::uint64_t value) {
  static_assert(std::is_integral<T>::value,
                "Type can only be uint64_t, uint32_t, uint16_t and uint8_t");
  std::bitset<sizeof(T) * 8> bits(value);
  return bits.to_string();
}

template <typename T> std::uint64_t StringToUint(const std::string &s) {
  static_assert(std::is_integral<T>::value,
                "Type can only be uint64_t, uint32_t, uint16_t and uint8_t");
  T value = 0;
  T x = 0;
  std::for_each(s.begin(), s.end(),
                [&x](const char &c) { x = (x << 1) + (c - '0'); });
  std::memcpy(&value, &x, sizeof(T));
  return value;
}

template <typename T>
bool approximatelyEqual(T a, T b, T epsilon)
{
    return std::fabs(a - b) <= ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

template <typename T>
bool essentiallyEqual(T a, T b, T epsilon)
{
    return std::fabs(a - b) <= ( (std::fabs(a) > std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

template <typename T>
bool definitelyGreaterThan(T a, T b, T epsilon)
{
    return (a - b) > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

template <typename T>
bool definitelyLessThan(T a, T b, T epsilon)
{
    return (b - a) > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

} // namespace ga
