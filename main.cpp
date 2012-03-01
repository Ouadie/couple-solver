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
#include "unit_num.h"
#include "force_vector.h"
#include "clear_term.h"

using namespace std;

vector<force_vector> storage; // stores inputed force vectors
string out_unit = "";         // the unit to print output, if empty uses unit of first vector

// help message, lists commands, and vector formats
string print_help() {
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
void change_unit(string unit) {
  if (Convert.toN(unit) != 0) {
    out_unit = unit;
    cout << "units set to " << unit << endl;
  } else
    cout << Convert.unknown_unit(unit) << endl;
}

// return the summation of all of the vectors stored in storage
// will return in the set units, or units of first inputted vector
force_vector vector_sum() {
  if (storage.size() == 0) {
    force_vector sum;
    return sum;
  } else {
    vector<force_vector>::iterator it = storage.begin();
    force_vector sum = *it; // initialse the sum so that units are correct
    it++;
    for (it; it < storage.end(); it++) {
      sum += *it;
    }
    if (out_unit != "")
      sum.change_unit(out_unit);
    return sum;
  }
}

void print_sum() {
  force_vector sum = vector_sum();
  cout << "sum: " << sum << endl;               // sum of vectors in cartisean
  cout << "     " << sum.to_coord_dir() << endl;  // sum of vectors in coord dir format
}

// indexes and lists all vectors in storage
// and the summation of them
// TODO make this cleaner, maybe more table-y?
void list_vectors() {
  if (storage.size() == 0)
    cout << "No vectors" << endl;
  else {

    for (int i = 0, length = storage.size(); i < length; i++) {
      cout << i << ":  " << storage[i] << endl;          // vector in cartesian format
      cout << "    " << storage[i].to_coord_dir() << endl; // vector in coord dir format
      cout << endl;
    }
    force_vector sum = vector_sum();
    cout << "sum: " << sum << endl;               // sum of vectors in cartisean
    cout << "     " << sum.to_coord_dir() << endl;  // sum of vectors in coord dir format
  }
}

// removes vector at idx from storage
// if 'all' is passed removes all vectors
void remove_vector(string idx) {
  if (idx == "all") {  // clear all vectors and reset output unit
    storage.clear();
    out_unit = "";
    cout << "Vectors cleared." << endl;
  } else if (numerical(idx)) { // idx is a number
    int pos = atoi(idx.c_str());
    if (pos >= 0 && pos < storage.size()) {
      vector<force_vector>::iterator it = storage.begin(); // stupid vector stuff, only takes iterator, so make an iterator
      it += pos;                                          // move it to the position
      storage.erase(it);                                  // and remove the vector
    } else {
      cout << "Index out of range." << endl;
    }
  } else
    cout << "Illegal argument: " << idx << endl;
  list_vectors();
}

// parses input into a vector, cleaning whitespace, commas and parens
void parse_input(const string &input, vector<string> &data) {
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

void add_vector(force_vector vector) {
  storage.push_back(vector);
  cout << "Added vector " << storage.size() - 1 << ": " << storage.back() << endl;
}

void add_point_to_point(double mag, string unit, double x1, double y1, double z1, double x2, double y2, double z2){
  try { 
    force_vector a(mag, unit, x1, y1, z1, x2, y2, z2);
    add_vector(a);
  } catch (string e) {
    cout << Convert.unknown_unit(e) << endl;
  } catch (exception& e) { // vector not legal
    cout << e.what() << endl;
  }
}

void add_coord(double mag, string unit, double alpha, double beta, double gama) {
  try {
    force_vector a(mag, unit, alpha, beta, gama);
    add_vector(a);
  } catch (exception& e) { // vector not legal, angles did not work out
    cout << e.what() << endl;
  } catch (string e) {
    cout << Convert.unknown_unit(e) << endl;
  }
}

void add_cartisian(double i, string u_i, double j, string u_j, double k, string u_k) {
  try {
    force_vector a(i, u_i, j, u_j, k, u_k);
    add_vector(a);
  } catch (string e) { // string not recognised as a unit
    cout << Convert.unknown_unit(e) << endl;
  }
}

void input_vector(vector<string> &data) {
  // input with 8 string or number values can be point to point or coordinate direction vectors
  if (data.size() == 8) {
    if (numerical((string[]){data[0], data[2], data[3], data[4], data[5], data[6], data[7]}, 7)) {
      add_point_to_point(atof(data[0].c_str()), data[1], 
          atof(data[2].c_str()), atof(data[3].c_str()), atof(data[4].c_str()), 
          atof(data[5].c_str()), atof(data[6].c_str()), atof(data[7].c_str()));
    }
    else if (numerical(data[0]) && // should be a coordinate angle vector, with 3 angles given
        numerical(data[2]) && numerical(data[4]) && numerical(data[6])) {
      add_coord(atof(data[0].c_str()), data[1], atof(data[2].c_str()), atof(data[4].c_str()), atof(data[6].c_str()));
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
        add_coord(atof(data[0].c_str()), data[1], alpha, beta, gama);
      } else { // cartisean vector
        add_cartisian(atof(data[0].c_str()), data[1], atof(data[2].c_str()), data[3], atof(data[4].c_str()), data[5]);
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
    parse_input(input, data); // this will parse the input, store it in data
    if (data.size() != 0) {
      // special case commands
      if (data[0] == "done" || data[0] == "exit")
        done = true;
      else if (data[0] == "list" || data[0] == "ls")
        list_vectors();
      else if (data[0] == "remove" || data[0] == "rm")
        remove_vector(data[1]);
      else if (data[0] == "sum")
        print_sum();
      else if (data[0] == "units") {
        if (data.size() > 1)
          change_unit(data[1]);
        else {
          out_unit = "";
          cout << "units cleared" << endl;
        }
      }
      else if (data[0] == "clear")
        ClearScreen();
      else if (data[0] == "help")
        cout << print_help() << endl;
      else { // if it's none of those it's probably a vector, or a mistake
        input_vector(data);
      }
    }
  }

  return 0;
}
