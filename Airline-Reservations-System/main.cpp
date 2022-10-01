/*
CS3520 Summer 2022
Leah Methratta
Assigns seats on each flight of the airline's only plane.
*/
#include "func.hpp"

// main function that runs all the code
int main() {

  // integer to store the user's input for the main menu
  int num;
  
  int seats[8][9] = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}};
  string chart;

  // appends the seating chart to the chart string
  assign(&seats, chart);

  // lists the main menu options
  main_menu();

  // begins the user interactions
  interact(num, "seating.txt", chart, seats);
}