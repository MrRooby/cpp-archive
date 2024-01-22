/** @file*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include "functions.h"
#include "structs.h"
#include "functions.cpp"

using namespace std;


int main(int argc, char* argv[])
{
    ///////////////////////////////// PRZEŁĄCZNIKI /////////////////////////////////

    bool z = argument_check(argc, argv);
    if (z == true) {
        return 0;
    }

    map<string, char*> arguments = f_ARGS(argc, argv);

    double extinction  = atof(arguments["-e"]);
    double mating      = atof(arguments["-m"]);
    int gen_num        = atoi(arguments["-g"]);
    int cross_num      = atoi(arguments["-c"]);
    string file_name   = string(arguments["-i"]);
    string output_name = string(arguments["-o"]);

    cout << "\nExtinction threshold:   " << extinction;
    cout << "\nMating threshold:       " << mating;
    cout << "\nNumber of generations:  " << gen_num;
    cout << "\nNumber of mixes:        " << cross_num;
    cout << "\nInput file name:        " << file_name;
    cout << "\nOutput file name:       " << output_name << endl;
    cout << endl;


    //////////////////////////// PRZYPISANIE ZMIENNYCH /////////////////////////////

    // string file_name;
    // string output_name;
    // int    gen_num;
    // int    cross_num;
    // double extinction;
    // double mating;

    
    ///////////////////////// WCZYTANIE DANYCH Z TERMINALA /////////////////////////

    // cout << "\nInsert input file name (must end with .txt):     ";
    // cin  >> file_name;
    // cout << "\nInsert number of wanted generations:             ";
    // cin  >> gen_num;
    // cout << "\nInsert number of wanted specimen mixes:          ";
    // cin  >> cross_num;  
    // cout << "\nInsert extinction threshold (range: 0.0 - 1.0):  ";
    // cin  >> extinction;
    // cout << "\nInsert mating threshold (range: 0.0 - 1.0):      ";
    // cin  >> mating;
    // cout << "\nInsert output file name (must end with .txt):    ";
    // cin  >> output_name;

    //////////////////////////// BŁĘDNE DANE WEJŚCIOWE /////////////////////////////

    ERRORS(gen_num, extinction, mating, cross_num);
    
    ///////// ZMIENNE DO SZYBKIEGO WYWOŁANIA FUNKCJI (PRZYKŁADOWE ZMIENNE) /////////

    // gen_num = 15;
    // cross_num = 5;
    // extinction = 0.13;
    // mating = 0.7;
    // file_name = "input_file.txt";
    // output_name = "output_file.txt";
    

    ////////////////////////////// WYKONANIE FUNKCJI ///////////////////////////////

    population Jackson;

    Jackson = read(file_name); 
    
    EVOLUTION(Jackson, gen_num, extinction, mating, cross_num);

    WRITE(Jackson, output_name);


    //////////////// TEST - WYPISANIE DANYCH DO TERMINALA - TEST ///////////////////

    int population_size = Jackson.specimen.size();
        
    for(int i = 0; population_size > i; i++)
    {
        int DNA_size = Jackson.specimen[i].DNA.size();
        cout << "[" << i << "] ";
        cout << "DNA size: " << DNA_size << "  | ";
        cout << "   f: {" << Jackson.specimen[i].indicator << "}         ";
        for(int k = 0; DNA_size > k; k++)
        {
            cout << Jackson.specimen[i].DNA[k] << ' ';
        }
        cout << endl;
    }
}
