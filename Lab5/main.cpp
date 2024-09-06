/**
 * Implementacion de Algoritmo de Genetico para resolver el problema de la mochila (knapsack). 
 * 
 * Autor: Dr. Edwin Villanueva
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <complex>
#define POPSIZE 10
#define GENERATIONS 100
#define TOURNAMENT_SIZE 3
#define MAX_INVESTMENT 1000.0
using namespace std;

struct Activo {
    double precio_actual;
    double precio_futuro_optimista;
    double precio_futuro_pesimista;

    Activo(double pa,double pfo,double pfp) : precio_actual(pa),precio_futuro_optimista(pfo), precio_futuro_pesimista(pfp){}
};

struct Individual {
    vector<int> chromosome;
    double fitness;

    Individual(vector<int> chromo) : chromosome(chromo), fitness(0) {}
};

void calculate_fitness(Individual& ind, vector<Activo>& assetPool) {
    double sumOptimist = 0.0;
    double sumPesimist = 0.0;
    double sum = 0.0;
    for (int i = 0; i < ind.chromosome.size(); ++i) {
        if (ind.chromosome[i] == 1) {
            sumOptimist += assetPool[i].precio_futuro_optimista;
            sumPesimist += assetPool[i].precio_futuro_pesimista;
            sum += assetPool[i].precio_actual;
        }
    }
    if(sum > MAX_INVESTMENT){
        ind.fitness = 0;
    }else{
        ind.fitness = fabs(sumOptimist - sum) - fabs(sumPesimist - sum);
    }
}

void evaluate_population(vector<Individual>& population, vector<Activo>& assetPool) {
    for (Individual& ind : population) {
        calculate_fitness(ind, assetPool);
    }
}

pair<Individual, Individual> crossover_onepoint(Individual& parent1, Individual& parent2) {
    int size = parent1.chromosome.size();
    int crossover_point = rand() % size;
    vector<int> child1_chromo(size);
    vector<int> child2_chromo(size);

    for (int i = 0; i < size; ++i) {
        child1_chromo[i] = (i < crossover_point) ? parent1.chromosome[i] : parent2.chromosome[i];
        child2_chromo[i] = (i < crossover_point) ? parent2.chromosome[i] : parent1.chromosome[i];
    }

    return make_pair(Individual(child1_chromo), Individual(child2_chromo));
}

pair<Individual, Individual> crossover_uniform(Individual& parent1, Individual& parent2) {
    int size = parent1.chromosome.size();
    vector<int> child1_chromo(size);
    vector<int> child2_chromo(size);

    for (int i = 0; i < size; ++i) {
        if (rand() % 2) {
            child1_chromo[i] = parent1.chromosome[i];
            child2_chromo[i] = parent2.chromosome[i];
        } else {
            child1_chromo[i] = parent2.chromosome[i];
            child2_chromo[i] = parent1.chromosome[i];
        }
    }

    return make_pair(Individual(child1_chromo), Individual(child2_chromo));
}

void mutation_flip(Individual& ind) {
    int position = rand() % ind.chromosome.size();
    ind.chromosome[position] = 1 - ind.chromosome[position];
}

vector<Individual> init_population(int population_size, int chromosome_length,vector<Activo>& assetPool,double maxInv) {
    vector<Individual> population;
    srand(time(0));
    for (int i = 0; i < population_size; ++i) {
        vector<int> chromosome(chromosome_length);
        for (int j = 0; j < chromosome_length; ++j) {
            chromosome[j] = rand() % 2;
        }
        population.push_back(Individual(chromosome));
    }
    return population;
}

vector<Individual> init_population1(int population_size,int chromosomeLength,vector<Activo>& assetPool,double maxInv){
    vector<Individual> poblacion;
    srand(time(0));
    while(poblacion.size() < population_size){
        vector<int> chromosome(chromosomeLength,0);
        double totalInv = 0.0;
        for (int i = 0; i < chromosomeLength; ++i) {
            if (rand() % 2 == 1 && totalInv + assetPool[i].precio_actual <= maxInv) {
                chromosome[i] = 1;
                totalInv += assetPool[i].precio_actual;
            }
        }

        if (totalInv <= maxInv) {
            poblacion.push_back(Individual(chromosome));
        }
    }
    return poblacion;
}

Individual tournament_selection(vector<Individual>& population, int tournament_size) {
    vector<Individual> tournament;
    for (int i = 0; i < tournament_size; ++i) {
        int random_index = rand() % population.size();
        tournament.push_back(population[random_index]);
    }

    return *max_element(tournament.begin(), tournament.end(), [](Individual& a, Individual& b) {
        return a.fitness < b.fitness;
    });
}



vector<Individual> select_survivors_ranking(vector<Individual>& population, vector<Individual>& offspring_population, int numsurvivors) {
    vector<Individual> next_population;
    population.insert(population.end(), offspring_population.begin(), offspring_population.end());
    sort(population.begin(), population.end(), [](Individual& a, Individual& b) {
        return a.fitness > b.fitness;
    });
    for (int i = 0; i < numsurvivors; ++i) {
        next_population.push_back(population[i]);
    }
    return next_population;
}

double genetic_algorithm(vector<Individual>& population, vector<Activo>& assetPool, 
        int generations, double mutation_rate, int tournament_size) {
    int popsize = population.size();
    evaluate_population(population, assetPool);
    vector<int> bestfitness;
    auto best_individual = max_element(population.begin(), population.end(), [](Individual& a, Individual& b) {
        return a.fitness < b.fitness;
    });
    // loop de generaciones
    for (int g = 0; g < generations; ++g) {
        
        // crea las parejas a cruzarse (mating pool)
        vector<pair<Individual, Individual>> mating_pool;
        for (int i = 0; i < popsize / 2; ++i) {
            mating_pool.push_back(make_pair(tournament_selection(population, tournament_size), tournament_selection(population, tournament_size)));
        }

        // cruza las parejas del mating pool. Cada cruzamiento genera 2 hijos
        vector<Individual> offspring_population;
        for (auto& parents : mating_pool) {  // por cada pareja del mating pool
            // pair<Individual, Individual> children = crossover_onepoint(parents.first, parents.second); // cruzamiento one point
            pair<Individual, Individual> children = crossover_uniform(parents.first, parents.second);  // cruzamiento uniforme

            if ((double)rand() / RAND_MAX < mutation_rate) { // intenta mutar el hijo 1 de acuerdo a la tasa de mutacion
                mutation_flip(children.first);
            }
            if ((double)rand() / RAND_MAX < mutation_rate) { // intenta mutar el hijo 2 de acuerdo a la tasa de mutacion
                mutation_flip(children.second);
            }
            offspring_population.push_back(children.first);  // agrega el hijo 1 a la poblacion descendencia
            offspring_population.push_back(children.second); // agrega el hijo 2 a la poblacion descendencia
        }

        evaluate_population(offspring_population, assetPool); // evalua poblacion descendencia
        population = select_survivors_ranking(population, offspring_population, popsize); // selecciona sobrevivientes por ranking

        // obtiene el mejor individuo de la poblacion sobreviviente
        best_individual = max_element(population.begin(), population.end(), [](Individual& a, Individual& b) {
            return a.fitness < b.fitness;
        });
    }

    return best_individual->fitness;
}

int main() {
    vector<Activo> assetPool = {
        {100, 150, 80}, {200, 250, 180}, {150, 220, 130}, {120, 180, 100}, {180, 230, 160},
        {110, 170, 90}, {130, 200, 110}, {160, 210, 140}, {140, 190, 120}, {210, 270, 190},
        {170, 240, 150}, {190, 260, 170}, {220, 300, 200}, {200, 280, 180}, {180, 250, 160},
        {195, 260, 175}, {205, 275, 185}, {215, 285, 195}, {225, 295, 205}, {235, 305, 215}
    };

    

    vector<double> tasasMutacion = {0.0, 0.4, 0.8};

    for(double tasaMutacion : tasasMutacion){
        double promedio = 0.0;
        for(int i=0;i<10;++i){
            vector<Individual> poblacion = init_population1(POPSIZE,assetPool.size(),assetPool,MAX_INVESTMENT);
            promedio += genetic_algorithm(poblacion,assetPool,GENERATIONS,tasaMutacion,TOURNAMENT_SIZE);
        }
        cout<< "Promedio Mejor: " << tasaMutacion << " - " << promedio/10.0 <<endl;
    }

    return 0;
}
