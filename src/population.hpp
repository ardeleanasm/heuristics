#pragma once
#include "chromosome.hpp"
namespace ga {
template <typename T, Config conf>
class Population {
  static_assert(conf.populationSize > 0,
                "Population size cannot be negative or zero");

public:
  Population();
  Population(const Population<T, conf> &population);
  Population(Population<T, conf> &&population);
  Population &operator=(const Population<T, conf> &population);
  Population &operator=(Population<T, conf> &&population);
  void RegisterChromosomeGenerator(
      std::function<void(Chromosome<T, conf> &)> f);
  void
  RegisterFitnessFunction(std::function<void(Chromosome<T, conf> &)> f);
  void GeneratePopulation();
  void EvaluatePopulation();
  T GetTotalFitnessValue() const;
  [[nodiscard]] std::array<Chromosome<T,conf>,conf.populationSize> GetPopulation() const {
      return aChromosomePopulation;
  }

  [[nodiscard]] Chromosome<T,conf> GetChromosome(const std::size_t position) const
  {
      assert(position>=0 && position<conf.populationSize);
      return aChromosomePopulation[position];
  }

  void SelectChromosome(const std::size_t position) {
      assert(position>=0 && position<conf.populationSize);
      aChromosomePopulation[position].Select();
  }
  void UnselectChromosome(const std::size_t position) {
      assert(position>=0 && position<conf.populationSize);
      aChromosomePopulation[position].Unselect();
  }

  void UnselectAll() {
    for(std::size_t i=0;i<conf.populationSize;i++) {
	UnselectChromosome(i);
    }
  }

  void SetChromosome(const Chromosome<T,conf> &c, const std::size_t position);
  Chromosome<T,conf> GetBestChromosome() const;
  Chromosome<T,conf> GetBestSelectedChromosome() const;
private:
  std::array<Chromosome<T, conf>, conf.populationSize> aChromosomePopulation;
  std::function<void(Chromosome<T, conf> &)> fChromosomeGenerator;
  std::function<void(Chromosome<T, conf> &)> fFitnessFunction;
};

template <typename T, Config conf>
Population<T, conf>::Population() {
  aChromosomePopulation.fill(Chromosome<T, conf>());
}

template <typename T, Config conf>
Population<T, conf>::Population(
    const Population<T, conf> &population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
  fFitnessFunction = population.fFitnessFunction;
}

template <typename T, Config conf>
Population<T, conf>::Population(
    Population<T, conf> &&population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
  fFitnessFunction = population.fFitnessFunction;
}

template <typename T, Config conf>
Population<T, conf> &
Population<T, conf>::operator=(
    const Population<T, conf> &population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
  fFitnessFunction = population.fFitnessFunction;
  return *this;
}

template <typename T, Config conf>
Population<T, conf> &
Population<T, conf>::operator=(
    Population<T, conf> &&population) {
  aChromosomePopulation = population.aChromosomePopulation;
  fChromosomeGenerator = population.fChromosomeGenerator;
  fFitnessFunction = population.fFitnessFunction;
  return *this;
}

template <typename T, Config conf>
void Population<T, conf>::RegisterChromosomeGenerator(
    std::function<void(Chromosome<T, conf> &)> f) {
  fChromosomeGenerator = f;
}

template <typename T, Config conf>
void Population<T, conf>::RegisterFitnessFunction(
    std::function<void(Chromosome<T, conf> &)> f) {
  fFitnessFunction = f;
}

template <typename T, Config conf>
void Population<T, conf>::GeneratePopulation() {
  std::for_each(aChromosomePopulation.begin(), aChromosomePopulation.end(),
                fChromosomeGenerator);
}
template <typename T, Config conf>
void Population<T, conf>::EvaluatePopulation() {
  std::for_each(aChromosomePopulation.begin(), aChromosomePopulation.end(),
                fFitnessFunction);
}

template <typename T, Config conf>
void Population<T,conf>::SetChromosome(const Chromosome<T,conf> &c, const std::size_t position)
{
    assert(position>=0 && position<conf.populationSize);
    aChromosomePopulation[position] = c;
}

template <typename T, Config conf>
Chromosome<T,conf> Population<T,conf>::GetBestChromosome() const
{
    auto chromosome = std::max_element(aChromosomePopulation.begin(),aChromosomePopulation.end(),[](const auto &lhs, const auto &rhs){
	    return lhs.GetFitnessValue() < rhs.GetFitnessValue(); 
	    });

    return static_cast<Chromosome<T,conf>>(*chromosome);
}
template <typename T, Config conf>
Chromosome<T,conf> Population<T,conf>::GetBestSelectedChromosome() const
{

    auto chromosome = std::max_element(aChromosomePopulation.begin(),aChromosomePopulation.end(),[](const auto &lhs, const auto &rhs){
	    return (lhs.GetFitnessValue() < rhs.GetFitnessValue() &&
		   lhs.IsSelected() && rhs.IsSelected()); 
	    });

    return static_cast<Chromosome<T,conf>>(*chromosome);
}

template <typename T, Config conf>
T Population<T,conf>::GetTotalFitnessValue() const {
    return std::accumulate(aChromosomePopulation.begin(),aChromosomePopulation.end(),0,[](T i, const Chromosome<T,conf> &chr) {
	    return i+chr.GetFitnessValue();
	    });
}

} // namespace ga

