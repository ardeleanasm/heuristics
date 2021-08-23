#pragma once

namespace ga
{
    template<typename T, std::size_t populationSize, std::size_t geneLength>
    class Selection 
    {
	public:
	    virtual ~Selection() {}
	    virtual void Select()=0;
    };

    template<typename T, std::size_t populationSize, std::size_t geneLength>
    class TournamentSelection: public Selection<T,populationSize,geneLength>
    {
	public:
	    void Select() override
	    {
		//TODO:Some implementation
	    }
	private:
    };

    template<typename T, std::size_t populationSize, std::size_t geneLength>
    class SelectionObjectAbstractFactory {

	public:
	    virtual std::shared_ptr<Selection<T,populationSize,geneLength>> CreateSelectionObject() const = 0;	    
    };

    template<typename T, std::size_t populationSize, std::size_t geneLength>
    class SelectionObjectFactory: public SelectionObjectAbstractFactory<T,populationSize,geneLength> {
	std::shared_ptr<Selection<T, populationSize,geneLength>> CreateSelectionObject() const override {
	    return std::shared_ptr<Selection<T,populationSize,geneLength>>(new TournamentSelection<T,populationSize,geneLength>());
	}
    };
}
