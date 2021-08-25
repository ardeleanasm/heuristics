#pragma once

namespace ga
{
    template<typename T, Config conf>
    class Selection 
    {
	public:
	    virtual ~Selection() {}
	    virtual Chromosome<T,conf> Select(Population<T,conf> &population)=0;

    };

    template<typename T, Config conf>
    class TournamentSelection: public Selection<T,conf>
    {
	public:
	    Chromosome<T,conf> Select(Population<T,conf> &population) override
	    {
		for(std::size_t i=0;i<conf.tournamentSize; i++) {
		    auto randomChromosomeIndex = uniform<std::size_t>(0,conf.populationSize);
		    population.SelectChromosome(randomChromosomeIndex);

		}
		auto bestChromosome = population.GetBestSelectedChromosome();
		population.UnselectAll();	
		return bestChromosome;
	    }
	private:
    };

    template<typename T, Config conf>
    class SelectionObjectAbstractFactory {

	public:
	    virtual std::shared_ptr<Selection<T,conf>> CreateSelectionObject() const = 0;	    
    };

    template<typename T, Config conf>
    class SelectionObjectFactory: public SelectionObjectAbstractFactory<T,conf> {
	std::shared_ptr<Selection<T,conf>> CreateSelectionObject() const override {
	    return std::shared_ptr<Selection<T,conf>>(new TournamentSelection<T,conf>());
	}
    };
}
