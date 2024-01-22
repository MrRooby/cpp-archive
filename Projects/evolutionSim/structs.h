/** @file */

// STRUKTURY PROJEKTU

#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <utility> 
#include <string>
#include <map>


/**
 * @brief Struktura osobnika
 * 
 * @param DNA - vector integer'ów zawierający uporządkowany chromosom osobnika
 * @param indicator - indywidualny współczynnik każdego osobnika (w zakresie 0-1)
 */
struct subject
{
    std::vector<std::size_t> DNA;
    double indicator;
};

/**
 * @brief Struktura populacji
 * 
 * @param specimen - vector zawierający struktury pojedynczych osobników
 */
struct population
{
    std::vector<subject> specimen;
};


#endif