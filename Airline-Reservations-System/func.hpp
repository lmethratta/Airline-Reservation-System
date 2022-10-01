#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

void main_menu();

void get_name(string &fname, string &lname);

void display(string chart);

void assign(int (*seats)[8][9], string &str);

void save_seats(string filename, string line);

void load_seats(string filename, string &line);

void load_vector(string filename, vector <string> &v);

void update(vector <string> &v, string &str, string seat);

void cancel(vector <string> &v, string &str, string seat, string name);

void add_bp(string name, string seat, string level, string &bp);

string get_col(int col);

string get_bp(string seat);

void print_manifest(int i, vector <string> v);

void book_seat(string filename, string &line, int row, int col);

string fc_full(int seats[][9]);

string bc_full(int seats[][9]);

void move_fcseat(string filename, string &chart, string &bp, int seats[][9]);

void move_bcseat(string filename, string &chart, string &bp, int seats[][9]);

void init_assignment(string filename, string &chart, string &bp, int seats[][9]);

void interact(int num, string filename, string &chart, int seats[][9]);