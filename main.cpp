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
#include "numerical.h"
#include "clear_term.h"

#include "unit_num.h"
#include "force_vector.h"
#include "system.h"

using namespace std;

my_system sys;
vector<force_vector> storage; // stores inputed force vectors
string out_unit = "";         // the unit to print output, if empty uses unit of first vector

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

void add_force(vector<string> &data) {
  data.erase(data.begin()); // remove what was the command
  string elem = data[0];
  data.erase(data.begin()); // remove what was the element name
  if (data[0] != "=") {
    cout << "Unexpected argument " << data[0] << endl;
    return;
  }
  data.erase(data.begin()); // remove what was the equal sign
  try {
    force_vector a(data);
    sys.forces[elem] = a;
    cout << "Added force " << elem << ": " << a << endl;
  } catch (exception& e) { // vector not legal, angles did not work out
    cout << e.what() << endl;
  } catch (string e) {
    cout << Convert.unknown_unit(e) << endl;
  }
}

void add_moment(vector<string> &data) {
  data.erase(data.begin()); // remove what was the command
  string elem = data[0];
  data.erase(data.begin()); // remove what was the element name
  if (data[0] != "=") {
    cout << "Unexpected argument " << data[0] << endl;
    return;
  }
  data.erase(data.begin()); // remove what was the equal sign
  try {
    force_vector a(data);
    sys.moments[elem] = a;
    cout << "Added moment " << elem << ": " << a << endl;
  } catch (exception& e) {
    cout << e.what() << endl;
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
      else if (data[0] == "list" || data[0] == "ls") {
        if (data[1] == "forces" || data[1] == "f")
          cout << sys.forces << endl;
        else  if (data[1] == "moments" || data[1] == "m")
          cout << sys.moments << endl;
      } 
      else if (data[0] == "remove" || data[0] == "rm")
        remove_vector(data[1]);
      else if (data[0] == "sum")
        print_sum();
      else if (data[0] == "units")
        change_unit(data);
      else if (data[0] == "clear")
        ClearScreen();
      else if (data[0] == "force")
        add_force(data);
      else if (data[0] == "moment")
        add_moment(data);
    }
  }

  return 0;
}
