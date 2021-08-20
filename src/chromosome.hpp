#pragma once

namespace ga {
template <typename T, std::size_t geneLength> class Chromosome {
  static_assert(std::is_floating_point<T>::value,
                "Fitness value type can only be float or double");
  static_assert(geneLength>0, "Gene size cannot be negative or zero");
public:
  Chromosome() {sGenes="";}
  Chromosome(const std::string &genes);
  Chromosome(const Chromosome<T, geneLength> &chromosome);

  Chromosome(Chromosome<T, geneLength> &&) = delete;
  Chromosome &operator=(const Chromosome<T, geneLength> &chromosome);

  Chromosome &operator=(Chromosome<T, geneLength> &&) = delete;

  [[nodiscard]] std::string GetGenes() const { return sGenes; }

  [[nodiscard]] T GetFitnessValue() const { return gFitnessValue; }

  void SetFitnessValue(const T value);

  void Initialize();
private:
  T gFitnessValue;
  std::string sGenes;
  static constexpr std::size_t gGeneLength = geneLength;
};

template <typename T, std::size_t geneLength>
Chromosome<T, geneLength>::Chromosome(const std::string &genes) {
  sGenes = genes;
}

template <typename T, std::size_t geneLength>
Chromosome<T, geneLength>::Chromosome(
    const Chromosome<T, geneLength> &chromosome) {
  sGenes = chromosome.sGenes;
}

template <typename T, std::size_t geneLength>
Chromosome<T, geneLength> &Chromosome<T, geneLength>::operator=(
    const Chromosome<T, geneLength> &chromosome) {
  sGenes = chromosome.sGenes;
  return *this;
}

template <typename T, std::size_t geneLength>
void Chromosome<T, geneLength>::SetFitnessValue(const T value) {
  gFitnessValue = value;
}

template <typename T, std::size_t geneLength>
void Chromosome<T,geneLength>::Initialize() {
    ga::Randomize<geneLength> rndGenerator;
    std::uint8_t rndGene = rndGenerator.generate();
    sGenes = ga::UintToString<std::uint8_t>(rndGene);
}

} // namespace ga
