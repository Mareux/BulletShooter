//
// Created by Mariia Nosko on 29.08.2021.
//

#include "Randomizer.h"

float Randomizer::RandomBetweenTwoFloat(float min, float max) {
        return (min + 1) + (((float) rand()) / (float) RAND_MAX) * (max - (min + 1));
}
