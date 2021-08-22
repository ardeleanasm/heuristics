#pragma once

namespace ga
{
    template <typename T,std::size_t populationSize, std::size_t geneLength>
    class GeneticAlgorithm
    {
	public:
	    GeneticAlgorithm(
		    std::function<void(Chromosome<T,geneLength> &)> chromosomeGenerator,
		    std::function<void(Chromosome<T,geneLength> &)> fitnessFunction
		    );
	    void Initialize();
	    void Run();
	private:
	    void Crossover();
	    void Mutate();
	    void Evolve();
	    Population<T,populationSize,geneLength> gPopulation;
	    std::function<void(Chromosome<T,geneLength> &)> fChromosomeGenerator;
	    std::function<void(Chromosome<T,geneLength> &)> fFitnessFunction;
	    std::function<void(const Population<T,populationSize,geneLength> &)> fNewGenerationCbk;
    };


template <typename T, std::size_t populationSize,std::size_t geneLength>
GeneticAlgorithm<T,populationSize,geneLength>::GeneticAlgorithm(
	std::function<void(Chromosome<T,geneLength> &)> chromosomeGenerator,
	std::function<void(Chromosome<T,geneLength> &)> fitnessFunction
	)
{
    fChromosomeGenerator = chromosomeGenerator;
    fFitnessFunction = fitnessFunction;
}


template <typename T, std::size_t populationSize, std::size_t geneLength>
void GeneticAlgorithm<T,populationSize,geneLength>::Initialize()
{
    gPopulation=Population<T,populationSize,geneLength>();
    gPopulation.RegisterChromosomeGenerator(fChromosomeGenerator);
    gPopulation.RegisterFitnessFunction(fFitnessFunction);
    gPopulation.GeneratePopulation();
    gPopulation.EvaluatePopulation();
}


template <typename T, std::size_t populationSize, std::size_t geneLength>
void GeneticAlgorithm<T,populationSize,geneLength>::Run()
{
}






}
