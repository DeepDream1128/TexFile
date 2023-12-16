#include <chrono>
#include "./algorithm.hpp"
#include<bits/stdc++.h>

int main() {
    // 物品重量
    // std::vector<int> weights = {80, 82, 85, 70, 72, 70, 66, 50, 55, 25, 50, 55, 40, 48, 50, 32, 22, 60, 30, 32, 40, 38, 35, 32, 25, 28, 30, 22, 50, 30, 45, 30, 60, 50, 20, 65, 20, 25, 30, 10, 20, 25, 15, 10, 10, 10, 4, 4, 2, 1};
    // // 物品价值
    // std::vector<int> values = {220, 208, 198, 192, 180, 180, 165, 162, 160, 158, 155, 130, 125, 122, 120, 118, 115, 110, 105, 101, 100, 100, 98, 96, 95, 90, 88, 82, 80, 77, 75, 73, 72, 70, 69, 66, 65, 63, 60, 58, 56, 50, 30, 20, 15, 10, 8, 5, 3, 1};
    // // 背包容量
    // int C = 1000;
    //物品重量和价值，按照您提供的样例数据
    // std::vector<int> weights = {80,82,85,70,72,70,82,75,78,45,49,76,45,35,94,49,76,79,84,74,76,63,35,26,52,12,56,78,16,52,16,42,18,46,39,80,41,41,16,35,70,72,70,66,50,55,25,50,55,40};
    // std::vector<int> values = {200,208,198,192,180,180,168,176,182,168,187,138,184,154,168,175,198,184,158,148,174,135,126,156,123,145,164,145,134,164,134,174,102,149,134,156,172,164,101,154,192,180,180,165,162,160,158,155,130,125};
    // // 背包容量更新为1000
    // int C = 1000;

    // std::vector<int> weights = {7,3,4,5};
    // std::vector<int> values = {42,12,40,25};
    // // 小样例的背包容量
   
    int C,n;
    std::vector<int> weights, values;
    std::ifstream file("./testfile/test03.txt");

    // 从文件读取背包容量和物品数量
    file >> C >> n;
    std::cout << "Capacity: " << C << std::endl;
    std::cout << "Number of items: " << n << std::endl;

    for (int i = 0; i < n; ++i) {
        int w, v;
        file >> w >> v;
        weights.push_back(w);
        values.push_back(v);
    }

    // 构造物品数组
    std::vector<Item> items;
    for (int i = 0; i < n; ++i) {
        items.push_back({weights[i], values[i]});
    }
    // 蛮力法求解背包问题
    // 注意：由于物品数量较多，这里不执行蛮力法，因为它的时间复杂度是O(2^n)，会非常耗时
    if (n <= 20) {
        auto start_bf = std::chrono::high_resolution_clock::now();
        int result_bf = knapsackBruteForce(items, C);
        auto end_bf = std::chrono::high_resolution_clock::now();
        std::cout << "Brute force: " << knapsackBruteForce(items, C) << std::endl;
        std::chrono::duration<double, std::milli> elapsed_bf = end_bf - start_bf;
        std::cout << "Elapsed time for brute force: " << elapsed_bf.count() << " ms\n";
    }
    else {
        std::cout << "Brute force: " << "N/A" << std::endl;
        std::cout << "Elapsed time for brute force: " << "N/A" << " ms\n";
        std::cout << "The number of items is too large for brute force." << std::endl;
    }
    // 动态规划（带滚动数组）求解背包问题
    auto start_dp = std::chrono::high_resolution_clock::now();
    int result_dp = knapsackDynamicRollingArray(items, C);
    auto end_dp = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_dp = end_dp - start_dp;
    std::cout << "Dynamic programming (rolling array): " << result_dp << std::endl;
    std::cout << "Elapsed time for dynamic programming: " << elapsed_dp.count() << " ms\n";

    // 遗传算法求解背包问题
    // 设置遗传算法的参数，如种群大小、代数、交叉率和变异率
    int populationSize = 20000; // 种群大小
    int generations = 50; // 代数
    double crossoverRate = 0.85; // 交叉率
    double mutationRate = 0.02; // 变异率
    int tournamentSize = 50; // 锦标赛的大小
    auto start_ga = std::chrono::high_resolution_clock::now();
    int result_ga = 0;
    while (result_ga < result_dp) {
        result_ga = knapsackGeneticAlgorithm(items, C, populationSize, generations, crossoverRate, mutationRate, tournamentSize);
        // result_ga = knapsackGeneticAlgorithm_o(items, C, populationSize, generations, crossoverRate, mutationRate);
        // std::cout << "Genetic algorithm: " << result_ga << std::endl;
    }
    auto end_ga = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_ga = end_ga - start_ga;
    // std::cout << "Genetic algorithm: " << result_ga << std::endl;
    std::cout << "Elapsed time for genetic algorithm: " << elapsed_ga.count() << " ms\n";

    return 0;
}
