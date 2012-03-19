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
#include "numerical.h"
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

// sets the default output unit
// if unit is unknown prints availiable units
void change_unit(vector<string> &data) {
  if (data.size() > 1) {
    if (Convert.toN(data[1]) != 0) {
      out_unit = data[1];
      cout << "units set to " << data[1] << endl;
    } else
      cout << Convert.unknown_unit(data[1]) << endl;
  }
  else {
    out_unit = "";
    cout << "units cleared" << endl;
  }
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

void add_vector(vector<string> &data) {
  try {
    force_vector a(data);
    storage.push_back(a);
    cout << "Added vector " << storage.size() - 1 << ": " << storage.back() << endl;
  } catch (exception& e) { // vector not legal, angles did not work out
    cout << e.what() << endl;
  } catch (string e) {
    cout << Convert.unknown_unit(e) << endl;
  }
}


void input_point(vector<string> data) {
  // add a point to the system
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
        change_unit(data);
      }
      else if (data[0] == "clear")
        ClearScreen();
      else if (data[0] == "help")
        cout << print_help() << endl;
      else if (data[0] == "force")
        add_vector(data);
      else if (data[0] == "point")
        add_vector(data);
      else {
        add_vector(data);
      }
    }
  }

  return 0;
}
