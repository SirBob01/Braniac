#ifndef CHESS_NEURAL_BRAIN_H_
#define CHESS_NEURAL_BRAIN_H_

#include <algorithm>
#include <vector>
#include <fstream>
#include <cstring>
#include <cassert>

#include "species.h"
#include "activations.h"
#include "phenome.h"

namespace chess::neural {
    /**
     * Test if a adding a new edge will create a cycle in the graph
     */
    bool creates_cycle(std::unordered_map<Edge, EdgeGene, EdgeHash> edges, Edge new_edge);

    class Brain {
        std::vector<Specie *> _species;
        std::vector<Phenome *> _phenomes;

        std::vector<Point> _inputs;
        std::vector<Point> _outputs;
        NEATParameters _params;

        std::vector<Genome *> _elites;
        Genome *_global_best;

        int _generations;

        /**
         * Calculate the distance between genomes for speciation
         */
        double distance(Genome &a, Genome &b);

        /**
         * Perform sexual crossover between two genomes
         */
        Genome *crossover(Genome &a, Genome &b);

        /**
         * Add a new genome to an existing species, or create a new
         * one if it is too genetically distinct
         */
        void add_genome(Genome *genome);

        /**
         * Generate all the phenomes
         */
        void generate_phenomes();

        /**
         * Eliminate the worst in the population
         */
        void cull();

        /**
         * Randomly breed new genomes via mutation or crossover
         */
        void repopulate();

        /**
         * Randomly select a specie whose likelihoods depend on adjusted fitness sum
         */
        Specie *sample_specie();

    public:
        Brain(std::vector<Point> inputs, std::vector<Point> outputs, NEATParameters params);
        Brain(std::string filename);
        ~Brain();

        /**
         * Get the list of phenomes for training
         */
        std::vector<Phenome *> &get_phenomes();

        /**
         * Evolve to the next generation
         */
        void evolve();

        /**
         * Get the current generation number
         */
        int get_generations();

        /**
         * Get the fittest phenome of the current generation
         */
        Phenome get_fittest();

        /**
         * Save the current population to disk
         */
        void save(std::string filename);
    };
}

#endif