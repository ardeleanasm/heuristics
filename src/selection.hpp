#pragma once

namespace ga
{

    template<typename T, Config conf>
    class Selection 
    {
	public:
	    virtual ~Selection() {}
	    virtual Chromosome<T,conf> Select(population_t<conf,conf.populationSize> &population)=0;

    };

    template<typename T, Config conf>
    class TournamentSelection: public Selection<T,conf>
    {
	public:
	    Chromosome<T,conf> Select(population_t<conf,conf.populationSize> &population) override
	    {
		population_t<conf,conf.tournamentSize> selectedPopulation;
		for(std::size_t i=0;i<conf.tournamentSize; i++) {
		    std::size_t randomChromosomeIndex = uniform<std::size_t>(0,conf.populationSize);
		    selectedPopulation[i] = population[randomChromosomeIndex];
		}
		auto bestChromosome = std::max_element(
			selectedPopulation.begin(),
			selectedPopulation.end(),
			[](const auto &lhs, const auto &rhs) {
			    return lhs.GetFitnessValue() < rhs.GetFitnessValue();
			}
			);
		return static_cast<Chromosome<T,conf>>(*bestChromosome);
	    }
	private:
    };

    template<typename T, Config conf>
    class RouletteSelection: public Selection<T,conf>
    {
	public:
	    Chromosome<T,conf> Select(population_t<conf,conf.populationSize> &population) override
	    {
		Chromosome<T,conf> selectedIndividual;
		bool isFound = false;
		double totalFitnessValues = 0.0;
		for(std::size_t i=0;i<conf.populationSize;i++) {
		    aRelativeProbabilities[i]=population[i].GetFitnessValue();
		    totalFitnessValues +=aRelativeProbabilities[i];
		}
		
		
		std::transform(aRelativeProbabilities.begin(),aRelativeProbabilities.end(),
			aRelativeProbabilities.begin(),[&](T value)-> T{return value/totalFitnessValues;});
		
		for(std::size_t i=0;i<conf.populationSize;i++) {
		    T sum = 0;
		    for(std::size_t j=0;j<=i;j++){
			sum+=aRelativeProbabilities[j];
		    }
		    aProbabilities[i]=sum;
		}
		double selectionProbability = uniform<double>(0,1);
		for (std::size_t j=0;j<conf.populationSize;j++) {
		    if (definitelyLessThan<double>(selectionProbability,aProbabilities[j],std::numeric_limits<double>::epsilon())) {
		        selectedIndividual = population[j];
			isFound = true;
		        break;
		    }
		}
		if (isFound) {
		    return selectedIndividual;
		}

		return population[0];
	    }
	private:
	    std::array<T, conf.populationSize> aRelativeProbabilities;
	    std::array<T,conf.populationSize> aProbabilities;
    };

    template<typename T, Config conf>
    class SelectionObjectAbstractFactory {

	public:
	    virtual std::shared_ptr<Selection<T,conf>> CreateSelectionObject(const SelectionMechanism &s) const = 0;	    
    };

    template<typename T, Config conf>
    class SelectionObjectFactory: public SelectionObjectAbstractFactory<T,conf> {
	std::shared_ptr<Selection<T,conf>> CreateSelectionObject(const SelectionMechanism &s) const override {
	    switch(s) {
		case ga::SelectionMechanism::TOURNAMENT_SELECTION: return std::shared_ptr<Selection<T,conf>>(new TournamentSelection<T,conf>());
		case ga::SelectionMechanism::ROULETTE_SELECTION: return std::shared_ptr<Selection<T,conf>>(new RouletteSelection<T,conf>());
	    }
	}
    };
}

