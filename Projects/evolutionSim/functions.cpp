/** @file*/

// DEFINICJE FUNKCJI PROJEKTU

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <random>
#include <map>
#include <iterator>

#include "functions.h"
#include "structs.h"

using namespace std;

///////////////////////////////////// WPISANIE PRZEŁĄCZNIKÓW DO MAPY ////////////////////////////////////

map<string, char*> f_ARGS(const int argc,char* argv[])
{
    map<string, char*> arguments;

    for (int i = 1; i < argc; i = i + 2)
    {
        arguments[argv[i]] = argv[i + 1]; 
    }
    return arguments;
}


//////////////////////////////////// TEST POPRAWNOŚCI PRZEŁĄCZNIKÓW ////////////////////////////////////

bool argument_check(const int argc,char* argv[])
{
    if (argc != 13) 
    {
        cout << "ERROR: Insufficient number of arguments / Space needed!";
        cout << endl;
        return true;
    }
    for (int i = 1; i < argc; i = i + 2)
    {
        if (string(argv[i]) == "-e" || string(argv[i]) == "-m" || string(argv[i]) == "-g" || string(argv[i]) == "-c" || string(argv[i]) == "-i" || string(argv[i]) == "-o") 
        {}
        else 
        {
            cout << "ERROR: Invalid arguments" << endl;
            cout << endl;
            return true;
        }
    }
    return false;
}


////////////////////////////////// TEST POPRAWNOŚCI DANYCH WEJŚCIOWYCH //////////////////////////////////

void ERRORS(const int gen_num, const double extinction, const double mating, const int cross_num)
{   
    if(gen_num < 0)
    {
        cout << "ERROR: Invalid number of wanted generations!" << endl;
        cout << endl;
    }
        
    if(extinction > 1)
    {
        cout << "ERROR: Invalid extiction threshold!" << endl;
        cout << endl;    
    }

    if(mating > 1)
    {
        cout << "ERROR: Invalid mating threshold!" << endl;
        cout << endl;
    }

    if(cross_num < 0)
    {
        cout << "ERROR: Invalid number of wanted mixes!" << endl;
        cout << endl;
    }
}


////////////////////////////////////// WCZYTANIE POPULACJI Z PLIKU //////////////////////////////////////

population read(const string file_name)
{           
    population Jackson;
    ifstream input_file(file_name);
  
    if(input_file.is_open())
    {
        string line;
        while(getline(input_file, line))
        {
            subject individual;            
            stringstream ss(line);
            int allel;
            
            while(ss >> allel)
            {
                individual.DNA.push_back(allel);
            }
            Jackson.specimen.push_back(individual);           
        }
        input_file.close();
    }
    else
        cout << "ERROR: Invalid file name!";

    return Jackson;
}


/////////////////////////////////// ZAPIS FINALNEJ POPULACJI DO PLIKU ////////////////////////////////////

void WRITE(const struct population Jackson, const string output_name)
{
    ofstream FinalPOP(output_name);
    
    for(int spec = 0; spec < Jackson.specimen.size(); spec++)
    {   
        int DNA_size = Jackson.specimen[spec].DNA.size();
        for(int i = 0; i < DNA_size; i++)
        {
            FinalPOP << Jackson.specimen[spec].DNA[i] << " ";
        }
        FinalPOP << endl;
    }
}


///////////////////////// DODANIE UTWORZONYCH OSOBNIKÓW DO TYMCZASOWEJ POPULACJI /////////////////////////

population newGEN(struct population& temp, const vector<int> new_specimen)
{
    int new_specimenDNA_size = new_specimen.size();
    subject temp_spec;
    for(int i = 0; i < new_specimenDNA_size; i++)
    {
        temp_spec.DNA.push_back(new_specimen[i]);
    }
    temp.specimen.push_back(temp_spec);

    return temp;
}


///////////// KALKULACJA WSPÓŁCZYNNIKA PRZYSTOSOWANIA DLA OSOBNIKÓW W TYMCZASOWEJ POPULACJI //////////////

void indicator(struct population& temp)
{
    int pop_size = temp.specimen.size();

    for(int k = 0; k < pop_size; k++)
    {
        double num_even = 0;
        double DNA_size = temp.specimen[k].DNA.size();
        for(int i = 0; i < DNA_size; i++)
        {
            if(temp.specimen[k].DNA[i] % 2 == 0)
            {
                num_even++;
            }
        }
        
        temp.specimen[k].indicator = (num_even/DNA_size);
    } 
}


////////////////////////////// SPRAWDZENIE PRZYSTOSOWANIA DO WARUNKÓW ////////////////////////////////////

void judgement_day(population& temp, const double mating, const double extinction)
{
    int pop_num = temp.specimen.size();
    
    for(int i = 0; i < pop_num; i++)
    {
        if(temp.specimen[i].indicator <= extinction)
        {
            temp.specimen.erase(temp.specimen.begin() + i);
            pop_num--;
            i--;
        }
        else if(temp.specimen[i].indicator >= mating)
        {
            temp.specimen.push_back(temp.specimen[i]);
        }
    }
}


////////////////////////////// SCALENIE POPULACJI TYMCZASOWEJ Z GŁÓWNĄ ///////////////////////////////////

void newGEN_entry(struct population& Jackson, const struct population temp)
{
    int temp_size = temp.specimen.size();
    for(int i = 0; i < temp_size; i++)
    {
        Jackson.specimen.push_back(temp.specimen[i]);
    }
}


//////////////////////////////// KRZYŻOWANIE / TWORZENIE NOWYCH OSOBNIKÓW ////////////////////////////////

void EVOLUTION(struct population& Jackson, const int gen_num, const double extinction, const double mating, const int cross_num)
{
    for(int gen = 0; gen < gen_num; gen++)
    {
        population temp;                                                            // tymczasowa populacja, do przechowania nowych osobników
        int pop_size = Jackson.specimen.size();
        
        random_device rand_num;                                                     // randomowy wybór
        uniform_int_distribution<int> pop_rand(0, pop_size-1);                      // osobników do krzyżówki

        for(int spec = 0; spec < cross_num; spec++)
        {
            map< int, pair< vector<size_t>, vector<size_t> > > cuts;
                   
            pair< vector<size_t>, vector<size_t> > cut_chrmosome;                   // para łącząca obie części chromosomu
            
            int ID_registry[2];                                                     // rejestr w celu sprawdzenia czy ten sam osobnik nie jest losowany 2x
            int DNA_size[2];                                                        // rejestr wielkości obu osobników do krzyżówki
            
            for(int pair = 0; pair < 2; pair++)
            {
                vector<size_t> temp_first;                                          // pierwsza połowa uciętego DNA
                vector<size_t> temp_second;                                         // druga    połowa uciętego DNA
                ID_registry[pair] = pop_rand(rand_num);
                while(ID_registry[0] == ID_registry[1])
                {
                    ID_registry[1] = pop_rand(rand_num);
                }

                DNA_size[pair] = Jackson.specimen[ID_registry[pair]].DNA.size();
                uniform_int_distribution<int> cut_rand(1, DNA_size[pair]-1);        // losujemy w którym miejscu ciąć chromosom
                int cut_point = cut_rand(rand_num);
                if(DNA_size[pair] == 2)
                {
                    cut_point = 1;
                }

                for(int i = 0; i < cut_point; i++)
                {
                    temp_first.push_back(Jackson.specimen[ID_registry[pair]].DNA[i]);
                }
                cut_chrmosome.first = temp_first;

                for(int i = cut_point; i < DNA_size[pair]; i++)
                {
                    temp_second.push_back(Jackson.specimen[ID_registry[pair]].DNA[i]);
                }
                cut_chrmosome.second = temp_second;
                cuts[pair] = cut_chrmosome;
            }   
            

            vector<int> new_specimen1;                                              // pierwszy tymczasowy osobnik do wprowadzenia do populacji

            for(int i = 0; i < cuts[0].first.size(); i++)                           // wprowadzanie danych z połówek do pierwszego nowego osobnika
            {
                new_specimen1.push_back(cuts[0].first[i]);           
            }

             for(int i = 0; i < cuts[1].second.size(); i++)
            {
                new_specimen1.push_back(cuts[1].second[i]);
            }
            temp = newGEN(temp, new_specimen1);

            
            vector<int> new_specimen2;                                              // drugi tymczasowy osobnik do wprowadzenia do populacji

            for(int i = 0; i < cuts[1].first.size(); i++)                           // wprowadzanie danych z połówek do drugiego nowego osobnika
            {
                new_specimen2.push_back(cuts[1].first[i]);           
            }

             for(int i = 0; i < cuts[0].second.size(); i++)
            {
                new_specimen2.push_back(cuts[0].second[i]);
            }
            temp = newGEN(temp, new_specimen2);
        }
    indicator(temp);

    judgement_day(temp, mating, extinction);

    newGEN_entry(Jackson, temp);
    }
}
