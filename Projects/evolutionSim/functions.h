/** @file */

// DEKLARACJE FUNKCJI PROJEKTU

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <utility> 
#include <string>
#include <map>

#include "structs.h"

/**
 * @brief Funkcja przypisuje przełączniki do mapy
 * 
 * @param argc ilość przełączników
 * @param argv tabela przełądzników
 * @return std::map<std::string, char*> - mapa przełączników
 */
std::map<std::string, char*> f_ARGS(const int argc,char* argv[]);


/**
 * @brief Funkcja sprawdza poprawność wprowadzonych przełączników
 * 
 * @param argc ilość przełączników
 * @param argv tabela przełądzników
 * @return true  - błędne przełączniki 
 * @return false - poprawne przełączniki
 */
bool argument_check(const int argc,char* argv[]);


/**
 * @brief Funkcja sprawdza czy wprowadzone dane funkcji są poprawne
 * 
 * @param gen_num - ilość oczekiwanych generacji
 * @param extinction - próg wymierania (wymierania)
 * @param mating - próg klonowania (rozmnażania)
 * @param cross_num - ilość oczekiwanych krzyżówek na generację 
 */
void ERRORS(const int gen_num, const double extinction, const double mating, const int cross_num);


/** @brief Funkcja odczytuje dane z pliku wejściowego
 *  @param file_name - nazwa wczytywanego pliku
 *  @return Jackson - funkcja zwraca początkową populację
*/
population read(const std::string file_name);


/**
 * @brief Funkcja tworzy plik wyjściowy z ostatecznym stanem głównej populacji
 * 
 * @param Jackson - struktura głównej populacji
 * @param output_name - nazwa pliku wyjściowego
 */
void WRITE(const struct population Jackson, const std::string output_name);


/**
 * @brief Funkcja tworzy nowego osobnika i dodaje go do tymczasowej populacji
 * 
 * @param temp - tymczasowa populacja
 * @param new_specimen - vector chromosomu skrzyżowanego osobnika
 * @return temp - aktualna tymczasowa populacja 
 */
population newGEN(struct population& temp, const std::vector<int> new_specimen);


/**
 * @brief Funkcja wyznacza współczynnik każdego osobnika tymczasowej populacji (procent parzystych allel z całego chromosomu)
 * 
 * @param temp - tymczasowa populacja
 */
void indicator(struct population& temp);


/**
 * @brief Funkcja ocenia i przesiewa populację tymczasową, odrzuca, klonuje lub pozostawia osobniki
 * 
 * @param temp - tymczasowa populacja
 * @param mating - próg rozmnażania (klonowania)
 * @param extinction - próg wymierania (odrzucania)
 */
void judgement_day(struct population& temp, const double mating, const double extinction);


/**
 * @brief Funkcja wprowadza tymczasową populację do głównej po zakończeniu pełnego cyklu generacji
 * 
 * @param Jackson - populacja główna
 * @param temp - populacja tymczasowa
 */
void newGEN_entry(struct population& Jackson, const struct population temp);


/**
 * @brief Funkcja cyklu ewolucji
 * 
 * @param Jackson - główna populacja 
 * @param gen_num - ilość oczekiwanych generacji
 * @param extinction - próg wymierania (wymierania)
 * @param mating - próg klonowania (rozmnażania)
 * @param cross_num - ilość oczekiwanych krzyżówek na generację
 * @see newGEN
 * indicator
 * judgement_day
 * newGEN_entry
 */
void EVOLUTION(struct population& Jackson, const int gen_num, const double extinction, const double mating, const int cross_num);


#endif