//
// Created by Mariia Nosko on 29.08.2021.
//

#include <random>
#include "Randomizer.h"

float Randomizer::RandomBetweenTwoFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}
