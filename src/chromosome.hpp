#pragma once

namespace ga {
template <typename T, Config conf> class Chromosome {
  static_assert(std::is_floating_point<T>::value,
                "Fitness value type can only be float or double");
  static_assert(conf.geneLength > 0, "Gene size cannot be negative or zero");

public:
  Chromosome() { sGenes = ""; gFitnessValue = 0; }
  Chromosome(const std::string &genes);
  Chromosome(const Chromosome<T, conf> &chromosome);

  Chromosome(Chromosome<T, conf> &&);
  Chromosome &operator=(const Chromosome<T, conf> &chromosome);

  Chromosome &operator=(Chromosome<T, conf> &&);

  void SetGenes(const std::string &gene) {
    assert(gene.length() == conf.geneLength);
    sGenes = gene;
  }

  [[nodiscard]] std::string GetGenes() const { return sGenes; }

  [[nodiscard]] T GetFitnessValue() const { return gFitnessValue; }

  void SetFitnessValue(const T value);

private:
  T gFitnessValue;
  std::string sGenes;
  static constexpr std::size_t gGeneLength = conf.geneLength;
};

template <typename T, Config conf>
Chromosome<T, conf>::Chromosome(const std::string &genes) {
  sGenes = genes;
  gFitnessValue = 0;
}

template <typename T, Config conf>
Chromosome<T, conf>::Chromosome(
    const Chromosome<T, conf> &chromosome) {
  sGenes = chromosome.sGenes;
  gFitnessValue = chromosome.gFitnessValue;
}

template <typename T, Config conf>
Chromosome<T, conf>::Chromosome(
    Chromosome<T, conf> &&chromosome) {
  sGenes = std::move(chromosome.sGenes);
  gFitnessValue = chromosome.gFitnessValue;
}
template <typename T, Config conf>
Chromosome<T, conf> &Chromosome<T, conf>::operator=(
    const Chromosome<T, conf> &chromosome) {
  sGenes = chromosome.sGenes;
  gFitnessValue = chromosome.gFitnessValue;
  return *this;
}

template <typename T, Config conf>
Chromosome<T, conf> &Chromosome<T, conf>::operator=(
    Chromosome<T, conf> &&chromosome) {
  sGenes = std::move(chromosome.sGenes);
  gFitnessValue = chromosome.gFitnessValue;
  return *this;
}
template <typename T, Config conf>
void Chromosome<T, conf>::SetFitnessValue(const T value) {
  gFitnessValue = value;
}
} // namespace ga
