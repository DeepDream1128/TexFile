#include <iostream>
#include <vector>
#include <functional> // For std::function
#include <climits>    // For INT_MIN
#include <algorithm> // For std::max
#include <bitset> // For brute force approach
#include <random> // For genetic algorithm
#include <ctime> // For seeding random number generator

// 定义物品结构体，包含重量和价值
struct Item {
    int weight;
    int value;
};

// 蛮力法求解背包问题
int knapsackBruteForce(const std::vector<Item>& items, int W) {
    int n = items.size();
    int max_value = 0;
    // 使用无符号长整型来确保位移操作不会溢出
    for (unsigned long long i = 0; i < (1ULL << n); ++i) {
        std::bitset<64> bits(i); // 改为64位，适用于物品数量不超过64的情况
        int value = 0, weight = 0;
        for (int j = 0; j < n; ++j) {
            if (bits[j]) {
                value += items[j].value;
                weight += items[j].weight;
            }
        }
        if (weight <= W && value > max_value) {
            max_value = value;
        }
    }
    return max_value;
}


// 动态规划（带滚动数组）求解背包问题
int knapsackDynamicRollingArray(const std::vector<Item>& items, int W) {
    std::vector<int> dp(W + 1);
    // 遍历每个物品
    for (const auto& item : items) {
        // 从后往前更新dp数组
        for (int i = W; i >= item.weight; --i) {
            // 更新当前重量的最大价值
            dp[i] = std::max(dp[i], dp[i - item.weight] + item.value);
        }
    }
    // 返回最大价值
    return dp[W];
}

// 遗传算法求解背包问题的辅助函数，计算总重量和总价值
std::pair<int, int> calculateTotal(const std::vector<Item>& items, const std::vector<int>& solution) {
    int total_weight = 0, total_value = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        if (solution[i]) {
            total_weight += items[i].weight;
            total_value += items[i].value;
        }
    }
    return {total_weight, total_value};
}

// 锦标赛选择机制
std::vector<int> tournamentSelection(const std::vector<std::vector<int>>& population, int tournamentSize, const std::function<int(const std::vector<int>&)>& fitnessFunc) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, population.size() - 1);
    std::vector<int> best;
    int bestFitness = INT_MIN;
    
    for (int i = 0; i < tournamentSize; ++i) {
        int idx = dist(rng); // 随机选择一个个体
        int currentFitness = fitnessFunc(population[idx]);
        if (currentFitness > bestFitness) {
            best = population[idx];
            bestFitness = currentFitness;
        }
    }
    
    return best;
}

// 遗传算法求解背包问题
int knapsackGeneticAlgorithm(std::vector<Item>& items, int W, int populationSize, int generations, double crossoverRate, double mutationRate, int tournamentSize) {
    // 初始化随机数生成器
    std::mt19937 rng(std::time(0));
    int answer = 0;
    // 定义初始种群，随机生成
    std::vector<std::vector<int>> population(populationSize, std::vector<int>(items.size()));
    for (auto& individual : population) {
        for (auto& gene : individual) {
            gene = rng() % 2; // 随机赋值0或1
        }
    }

    // 适应度函数，用于评估背包的总价值
    auto fitness = [&](const std::vector<int>& individual) {
        auto [total_weight, total_value] = calculateTotal(items, individual);
        // 如果总重量不超过背包容量，返回总价值；否则，惩罚超重的个体
        return total_weight <= W ? total_value : 0;
    };

    // 遗传算法的主循环
    for (int generation = 0; generation < generations; ++generation) {
        std::vector<std::vector<int>> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            // 使用锦标赛选择机制选择父母
            std::vector<int> parent1 = tournamentSelection(population, tournamentSize, fitness);
            std::vector<int> parent2 = tournamentSelection(population, tournamentSize, fitness);
            std::vector<int> child(items.size());

            // 交叉
            if (std::generate_canonical<double, 10>(rng) < crossoverRate) {
                int crossoverPoint = rng() % items.size();
                for (int j = 0; j < crossoverPoint; ++j) child[j] = parent1[j];
                for (int j = crossoverPoint; j < items.size(); ++j) child[j] = parent2[j];
            } else {
                child = parent1; // 如果不交叉，子代直接继承父代1的基因
            }

            // 变异
            for (int j = 0; j < items.size(); ++j) {
                if (std::generate_canonical<double, 10>(rng) < mutationRate) {
                    child[j] = 1 - child[j]; // 翻转基因
                }
            }

            // 将新个体添加到新种群中
            newPopulation.push_back(child);
        }

        // 用新种群替换旧种群
        population = newPopulation;
        std::sort(population.begin(), population.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
             return fitness(a) > fitness(b);
        });
        answer = std::max(answer, fitness(population.front()));
        if (generation % 10 == 0) {
            std::cout << "Generation " << generation << ": " << answer << std::endl;
        }
        
    }

    // 在最终种群中找到最优解
    std::sort(population.begin(), population.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
        return fitness(a) > fitness(b);
    });
    // 返回最大适应度值
    return answer;
}

int knapsackGeneticAlgorithm_o(std::vector<Item>& items, int W, int populationSize, int generations, double crossoverRate, double mutationRate) {
    // 初始化随机数生成器
    std::mt19937 rng(std::time(0));
    int answer = 0;
    // 定义初始种群，随机生成
    std::vector<std::vector<int>> population(populationSize, std::vector<int>(items.size()));
    for (auto& individual : population) {
        for (auto& gene : individual) {
            gene = rng() % 2; // 随机赋值0或1
        }
    }

    // 适应度函数，用于评估背包的总价值
    auto fitness = [&](const std::vector<int>& individual) {
        auto [total_weight, total_value] = calculateTotal(items, individual);
        return total_weight <= W ? total_value : 0; // 如果超重则惩罚该个体
    };

    // 遗传算法的主循环
    for (int generation = 0; generation < generations; ++generation) {
        // 计算种群的总适应度
        double total_fitness = std::accumulate(population.begin(), population.end(), 0.0, [&](double sum, const std::vector<int>& individual) {
            return sum + fitness(individual);
        });

        // 计算每个个体的选择概率
        std::vector<double> selection_probabilities;
        for (const auto& individual : population) {
            selection_probabilities.push_back(fitness(individual) / total_fitness);
        }

        // 轮盘赌选择
        std::vector<std::vector<int>> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            // 累计概率
            double cumulative_probability = 0.0;
            double r = std::generate_canonical<double, 10>(rng);
            for (size_t j = 0; j < population.size(); ++j) {
                cumulative_probability += selection_probabilities[j];
                if (r <= cumulative_probability) {
                    newPopulation.push_back(population[j]);
                    break;
                }
            }
        }

        // 交叉操作
        for (int i = 0; i < populationSize; i += 2) {
            if (std::generate_canonical<double, 10>(rng) < crossoverRate) {
                int crossoverPoint = rng() % items.size();
                for (int j = crossoverPoint; j < items.size(); ++j) {
                    std::swap(newPopulation[i][j], newPopulation[(i + 1) % populationSize][j]);
                }
            }
        }

        // 变异操作
        for (auto& individual : newPopulation) {
            for (int j = 0; j < individual.size(); ++j) {
                if (std::generate_canonical<double, 10>(rng) < mutationRate) {
                    individual[j] = 1 - individual[j];
                }
            }
        }

        // 替换旧种群
        population = std::move(newPopulation);
        std::sort(population.begin(), population.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
             return fitness(a) > fitness(b);
        });
        answer = std::max(answer, fitness(population.front()));
        if (generation % 10 == 0) {
            std::cout << "Generation " << generation << ": " << answer << std::endl;
        }
    }

    // 在最终种群中找到适应度最高的个体
    return answer;
}