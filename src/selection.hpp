#pragma once

namespace ga {

template <typename T, Config conf> class Selection {
public:
  virtual ~Selection() {}
  virtual Chromosome<T, conf> Select(Population<T, conf> &population) = 0;
};

template <typename T, Config conf>
class TournamentSelection : public Selection<T, conf> {
public:
  Chromosome<T, conf> Select(Population<T, conf> &population) override {
    for (std::size_t i = 0; i < conf.tournamentSize; i++) {
      auto randomChromosomeIndex = uniform<std::size_t>(0, conf.populationSize);
      population.SelectChromosome(randomChromosomeIndex);
    }
    auto bestChromosome = population.GetBestSelectedChromosome();
    population.UnselectAll();
    return bestChromosome;
  }

private:
};

template <typename T, Config conf>
class RouletteSelection : public Selection<T, conf> {
public:
  Chromosome<T, conf> Select(Population<T, conf> &population) override {
    for (std::size_t i = 0; i < conf.populationSize; i++) {
      aRelativeProbabilities[i] = population.GetChromosome(i).GetFitnessValue();
    }

    T totalFitnessValues = population.GetTotalFitnessValue();

    std::transform(aRelativeProbabilities.begin(), aRelativeProbabilities.end(),
                   aRelativeProbabilities.begin(),
                   [&](T value) -> T { return value / totalFitnessValues; });

    for (std::size_t i = 0; i < conf.populationSize; i++) {
      T sum = 0;
      for (std::size_t j = 0; j <= i; j++) {
        sum += aRelativeProbabilities[j];
      }
      aProbabilities[i] = sum;
    }
    for (std::size_t i = 0; i < conf.tournamentSize; i++) {
      double selectionProbability = uniform<double>(0, 1);
      for (std::size_t j = 0; j < conf.populationSize; j++) {
        if (definitelyLessThan<double>(
                selectionProbability, aProbabilities[j],
                std::numeric_limits<double>::epsilon())) {
          population.SelectChromosome(j);
          break;
        }
      }
    }
    auto bestChromosome = population.GetBestSelectedChromosome();
    population.UnselectAll();
    return bestChromosome;
  }

private:
  std::array<T, conf.populationSize> aRelativeProbabilities;
  std::array<T, conf.populationSize> aProbabilities;
};

template <typename T, Config conf> class SelectionObjectAbstractFactory {

public:
  virtual std::shared_ptr<Selection<T, conf>>
  CreateSelectionObject(const SelectionMechanism &s) const = 0;
};

template <typename T, Config conf>
class SelectionObjectFactory : public SelectionObjectAbstractFactory<T, conf> {
  std::shared_ptr<Selection<T, conf>>
  CreateSelectionObject(const SelectionMechanism &s) const override {
    switch (s) {
    case ga::SelectionMechanism::TOURNAMENT_SELECTION:
      return std::shared_ptr<Selection<T, conf>>(
          new TournamentSelection<T, conf>());
    case ga::SelectionMechanism::ROULETTE_SELECTION:
      return std::shared_ptr<Selection<T, conf>>(
          new RouletteSelection<T, conf>());
    }
  }
};
} // namespace ga
