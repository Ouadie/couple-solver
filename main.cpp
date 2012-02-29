/**********************************************\
* main.cpp                        vector adder *
* Caleb Everett                        statics *
*                                              *
* Main function, gets user input, passes data  *
* to vectors, shows sum                        *
\**********************************************/



#include <iostream>
#include <stdlib.h> // included for string to number conversion
#include <vector>  // resizeable array
#include "convert.h"
#include "unit.h"
#include "forceVector.h"
#include "clear_term.h"

using namespace std;

/*
 * 
 * vector<forceVector> storage;   stores inputed force vectors
 * string outUnit = "";           the unit to print output in.
 *
 * string printHelp();            prints the help message, which details commands, 
 *                                usage, and vector formats
 *
 * bool numerical(string test);   returns true if test only contains digits, hyphens, and
 *                                < 1 decimal 
 *
 * void changeUnit(string unit);  sets the output unit
 * forceVector vectorSum();       returns the sum of vectors in storage
 * void printSum();               prints the vectorSum() in cartesian and coordinate form
 * void listVectors();            prints all vectors, and the sum
 * void removeVector(string idx); removes vector as idx, or all vectors if idx is 'all'
 * void parseInput(string input,  parses input into data, removing all parens, whitespace,
 *         vector<string> data);  and commas
 *
 * void addVector(forceVector     adds vector to the list of known vectors
 *                     vector);   
 *
 * void addPointToPoint(...)      creates a vector from input in the form of
 *                                a magnatude and two points
 *
 * void addCoord(...)             creates a vector from input in the form of
 *                                a magnatude and coordinate directions
 *
 * void addCartisian(...)         creates a vector from input in the form of
 *                                cartesian magnatudes
 *  
 * void inputVector(...)          parses input data and attempts to add a vector
 *                                if the data's format matches any of the above
 * 
 * int main(void)                 reads input from user, checks if it matches any
 *                                commands, or is a vector. Exicute's the command
 *                                or adds the vector. Repeats untill 'exit' is inputed
 */

vector<forceVector> storage; // stores inputed force vectors
string outUnit = "";         // the unit to print output, if empty uses unit of first vector

// help message, lists commands, and vector formats
string printHelp() {
  string out = "";
  out += "This tool stores inputted vectors, and prints their summation\n"
         "To use this tool enter either a command or a vector you wish to be input\n"
         "Vector Formats:\n"
         " - unit components: x_component unit y_component unit z component unit\n"
         "   commas are allowed, but not nessesary\n"
         "     5 N 3 N 2 N\n"
         "     5 N, 3 N, 2 N\n"
         "     2 lb 3 lb 0 lb\n"
         "     2 lb 3 lb 0 N\n"
         "\n"
         " - coordinate direction: magnitude unit alpha_degrees a beta_degrees b gamma_degrees y"
         "   you must supply at least 2 of the following a,b,y\n"
         "     5 N 45 a 90 b\n"
         "     5 N 45 a 45 b 90 y\n"
         "     5 N 45 a 90 b\n"
         "\n"
         " - point to point: magnitude unit (x1,y1,z1) (x2,y2,z2)\n"
         "   the points cannot be the same\n"
         "     5 N (0,0,0) (0,1,0)\n"
         "     5 lb (1 0 0) (0 1 0)\n"
         "\n"

         "Commands:\n"
          " - help: print this message\n"
          " - list: list and index all vectors\n"
          " - remove IDX: removes vector IDX. If IDX is 'all' removes all vectors\n"
          " - sum:  prints the sum of inputed vectors\n"
          " - units UNIT: sets output to UNIT\n"
          " - clear: clears the console\n";
  return out;
}
// returns true if string is numerical (all charecters are digites or decimal)
bool numerical(string test) {
  if (test.find_first_not_of("0123456789.-") == test.npos) { // are there only digets, decimals or negative signs?
    int first = test.find_first_of("."); // yup, test if only one decimal
    return (test.find_first_of(".", first + 1) == test.npos); // only found one '.' test is a number
  } else
    return false; // nope were out
}

// tests that each element in an inputed array is numerical
bool numerical(string test[], int num){
  bool pass = true;
  for (int i = 0; i < num; i++){
    pass = numerical(test[i]);
    if (!pass) break;
  }
  return pass;
}

// sets the default output unit
// if unit is unknown prints availiable units
void changeUnit(string unit) {
  if (Convert.toN(unit) != 0) {
    outUnit = unit;
    cout << "units set to " << unit << endl;
  } else
    cout << Convert.unknown_unit(unit) << endl;
}

// return the summation of all of the vectors stored in storage
// will return in the set units, or units of first inputted vector
forceVector vectorSum() {
  if (storage.size() == 0) {
    forceVector sum;
    return sum;
  } else {
    vector<forceVector>::iterator it = storage.begin();
    forceVector sum = *it; // initialse the sum so that units are correct
    it++;
    for (it; it < storage.end(); it++) {
      sum += *it;
    }
    if (outUnit != "")
      sum.changeUnit(outUnit);
    return sum;
  }
}

void printSum() {
  forceVector sum = vectorSum();
  cout << "sum: " << sum << endl;               // sum of vectors in cartisean
  cout << "     " << sum.toCoordDir() << endl;  // sum of vectors in coord dir format
}

// indexes and lists all vectors in storage
// and the summation of them
// TODO make this cleaner, maybe more table-y?
void listVectors() {
  if (storage.size() == 0)
    cout << "No vectors" << endl;
  else {

    for (int i = 0, length = storage.size(); i < length; i++) {
      cout << i << ":  " << storage[i] << endl;          // vector in cartesian format
      cout << "    " << storage[i].toCoordDir() << endl; // vector in coord dir format
      cout << endl;
    }
    forceVector sum = vectorSum();
    cout << "sum: " << sum << endl;               // sum of vectors in cartisean
    cout << "     " << sum.toCoordDir() << endl;  // sum of vectors in coord dir format
  }
}

// removes vector at idx from storage
// if 'all' is passed removes all vectors
void removeVector(string idx) {
  if (idx == "all") {  // clear all vectors and reset output unit
    storage.clear();
    outUnit = "";
    cout << "Vectors cleared." << endl;
  } else if (numerical(idx)) { // idx is a number
    int pos = atoi(idx.c_str());
    if (pos >= 0 && pos < storage.size()) {
      vector<forceVector>::iterator it = storage.begin(); // stupid vector stuff, only takes iterator, so make an iterator
      it += pos;                                          // move it to the position
      storage.erase(it);                                  // and remove the vector
    } else {
      cout << "Index out of range." << endl;
    }
  } else
    cout << "Illegal argument: " << idx << endl;
  listVectors();
}

// parses input into a vector, cleaning whitespace, commas and parens
void parseInput(const string &input, vector<string> &data) {
  data.clear(); // clear out any data already in the vector
  int start = 0;
  int end = 0;
  do {
    start = input.find_first_not_of("(),\t ", end);
    end = input.find_first_of("(),\t ", start);
    if (start != -1)
      data.push_back(input.substr(start, end - start));
  } while (end != -1 || start != -1);
}

void addVector(forceVector vector) {
  storage.push_back(vector);
  cout << "Added vector " << storage.size() - 1 << ": " << storage.back() << endl;
}

void addPointToPoint(double mag, string unit, double x1, double y1, double z1, double x2, double y2, double z2){
  try { 
    forceVector a(mag, unit, x1, y1, z1, x2, y2, z2);
    addVector(a);
  } catch (string e) {
    cout << Convert.unknown_unit(e) << endl;
  } catch (exception& e) { // vector not legal
    cout << e.what() << endl;
  }
}

void addCoord(double mag, string unit, double alpha, double beta, double gama) {
  try {
    forceVector a(mag, unit, alpha, beta, gama);
    addVector(a);
  } catch (exception& e) { // vector not legal, angles did not work out
    cout << e.what() << endl;
  } catch (string e) {
    cout << Convert.unknown_unit(e) << endl;
  }
}

void addCartisian(double i, string u_i, double j, string u_j, double k, string u_k) {
  try {
    forceVector a(i, u_i, j, u_j, k, u_k);
    addVector(a);
  } catch (string e) { // string not recognised as a unit
    cout << Convert.unknown_unit(e) << endl;
  }
}

void inputVector(vector<string> &data) {
  // input with 8 string or number values can be point to point or coordinate direction vectors
  if (data.size() == 8) {
    if (numerical((string[]){data[0], data[2], data[3], data[4], data[5], data[6], data[7]}, 7)) {
      addPointToPoint(atof(data[0].c_str()), data[1], 
          atof(data[2].c_str()), atof(data[3].c_str()), atof(data[4].c_str()), 
          atof(data[5].c_str()), atof(data[6].c_str()), atof(data[7].c_str()));
    }
    else if (numerical(data[0]) && // should be a coordinate angle vector, with 3 angles given
        numerical(data[2]) && numerical(data[4]) && numerical(data[6])) {
      addCoord(atof(data[0].c_str()), data[1], atof(data[2].c_str()), atof(data[4].c_str()), atof(data[6].c_str()));
    } else {
      cout << "unrecognised input enter 'help' to se a list of inputs" << endl; // dont know what that is
    }
  } else if (data.size() == 6) {
    if (numerical((string[]){data[0], data[2], data[4]}, 3)) {
      if ( (data[3] == "a" || data[3] == "b" || data[3] == "y") && // two termed coordinate vector
           (data[5] == "a" || data[5] == "b" || data[5] == "y") ) {
        double alpha = -1, beta = -1, gama = -1;
        if (data[3] == "a") alpha = atof(data[2].c_str());
        else if (data[3] == "b") beta = atof(data[2].c_str());
        else if (data[3] == "y") gama = atof(data[2].c_str());

        if (data[5] == "a") alpha = atof(data[4].c_str());
        else if (data[5] == "b") beta = atof(data[4].c_str());
        else if (data[5] == "y") gama = atof(data[4].c_str());
        addCoord(atof(data[0].c_str()), data[1], alpha, beta, gama);
      } else { // cartisean vector
        addCartisian(atof(data[0].c_str()), data[1], atof(data[2].c_str()), data[3], atof(data[4].c_str()), data[5]);
      }
    } else {
      cout << "unrecognised input enter 'help' to se a list of inputs" << endl; // lok IDK?
    }
  }
}


// loops untill user inputs exit
// takes vectors and adds them, displaying the sum of all added vectors
int main(void) {
  string input; // place to store input string
  cout << "type help for instructions on using this tool" << endl;
  bool done = false;
  vector<string> data;  // this will store parsed input
  while (!done) { // keep looping till were done
    cout << "-> "; // print the user prompt
    getline (cin, input); // grab all user input, store it in input
    parseInput(input, data); // this will parse the input, store it in data
    if (data.size() != 0) {
      // special case commands
      if (data[0] == "done" || data[0] == "exit")
        done = true;
      else if (data[0] == "list" || data[0] == "ls")
        listVectors();
      else if (data[0] == "remove" || data[0] == "rm")
        removeVector(data[1]);
      else if (data[0] == "sum")
        printSum();
      else if (data[0] == "units") {
        if (data.size() > 1)
          changeUnit(data[1]);
        else {
          outUnit = "";
          cout << "units cleared" << endl;
        }
      }
      else if (data[0] == "clear")
        ClearScreen();
      else if (data[0] == "help")
        cout << printHelp() << endl;
      else { // if it's none of those it's probably a vector, or a mistake
        inputVector(data);
      }
    }
  }

  return 0;
}
