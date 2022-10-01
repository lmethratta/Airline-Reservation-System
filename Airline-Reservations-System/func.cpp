#include "func.hpp"

// Presents the main menu
void main_menu() {

  cout << "Enter a number from 1-9 for the following options:" << endl;
  cout << "(1) Load Previous “Seat Assignment and Passenger Manifest”" << endl;
  cout << "(2) Save Current “Seat Assignment and Passenger Manifest”" << endl;
  cout << "(3) Display the seating map/chart showing all seats and indicating "
          "if each seat is filled and which seats are assigned"
       << endl;
  cout << "(4) Choose a seat (with the help of automated system)" << endl;
  cout << "(5) Update a seat assignment" << endl;
  cout << "(6) Cancel seat assignment" << endl;
  cout << "(7) Print boarding pass" << endl;
  cout << "(8) Print Passenger Manifest" << endl;
  cout << "(9) Quit" << endl;
}

// Prompts the passenger for their name and stores it in the given variable
void get_name(string &fname, string &lname) {
  cout << "What is your first name?" << endl;
  cin >> fname;
  cout << endl;
  cout << "What is your last name?" << endl;
  cin >> lname;
  cout << endl;
}

// Prints the seating chart
void display(string chart) { cout << chart << endl; }

// Appends the seating chart to a given string
void assign(int (*seats)[8][9], string &str) {
  for (auto &row : *seats) {
    for (auto &e : row) {
      str += to_string(e) + " ";
    }
    str += "\n";
  }

  str = str.substr(0, str.size() - 1);
}

// Saves the seats to a text file
void save_seats(string filename, string line) {
  // opens file
  ofstream outfile(filename);
  if (!outfile) {
    cout << "can't open the file" << endl;
    exit(EXIT_FAILURE);
  }

  outfile << line.substr(0, line.size() - 1) << endl;
}

// opens the given text file and uses a vector to append the file's contents to the given string
void load_seats(string filename, string &line) {
  vector<string> v;
  // opens text file
  ifstream infile(filename);
  if (!infile) {
    cout << "can't open the file" << endl;
    exit(EXIT_FAILURE);
  }

  while (getline(infile,line)) {
    v.push_back(line);
  }

  for (auto& row: v) {
    line += row + "\n";
  }
}

// loads the contents of a file into a vector
void load_vector(string filename, vector <string> &v) {
  string line;
  
  // opens text file
  ifstream infile(filename);
  if (!infile) {
    cout << "can't open the file" << endl;
    exit(EXIT_FAILURE);
  }

  while (getline(infile,line)) {
    v.push_back(line);
  }
}

// Updates the passenger manifest to change the name on one to the boarding passes
void update(vector <string> &v, string &str, string seat) {
  str = "";
  for (auto& row: v) {
    if (row.find(seat) != string::npos) {
      string name_change;
      string seat_change;
      string fname;
      string lname;
      auto it = find(v.begin(), v.end(), row);
      int index = it - v.begin();
      
      cout << "Press 'n' to change name" << endl;
      cin >> name_change;
      cout << endl;
      if (name_change == "n") {
        cout << "Enter a new first name:" << endl;
        cin >> fname;
        cout << endl;
        cout << "Enter a new last name:" << endl;
        cin >> lname;
        cout << endl;
        
        str += row.substr(0, row.find("Name: ") + 6) + fname + " " + lname + "," + row.substr(row.find(" Seat"), row.size()) + "\n";
      }
      else {
        str += row + "\n";
      }
    }
    else {
      str += row + "\n";
    }
  }
  save_seats("boarding_passes.txt", str.substr(0, str.size() - 1));
}

// cancels a booked flight
void cancel(vector <string> &v, string &str, string seat, string name) {
  str = "";
  for (auto& row: v) {
    if (!((row.find(seat) != string::npos) && (row.find(name) != string::npos))) {
      str += row + "\n";
    }
  }
  save_seats("boarding_passes.txt", str.substr(0, str.size() - 1));
}

// Adds boarding pass to file
void add_bp(string name, string seat, string level, string &bp) {
  ofstream outfile("boarding_passes.txt");
  if (!outfile) {
    cout << "can't open the file" << endl;
    exit(EXIT_FAILURE);
  }

  if (bp == "") {
    bp = "Name: " + name + ", Seat: " + seat + ", Level: " + level;
  }
  else {
    bp += "Name: " + name + ", Seat: " + seat + ", Level: " + level;
  }

  outfile << bp << endl;
}

// Converts column number to letter
string get_col(int col) {
  switch (col) {
    case 1:
      return "A";
      break;
    case 2:
      return "B";
      break;
    case 3:
      return "D";
      break;
    case 4:
      return "E";
      break;
    case 5:
      return "F";
      break;
    case 6:
      return "G";
      break;
    case 7:
      return "I";
      break;
    case 8:
      return "J";
      break;
    case 9:
      return "K";
      break;
    default:
      return "Invaild Column Value";
      break;
  }
}

// gets the boarding pass at the given seat
string get_bp(string seat) {
  string line;
  // opens text file
  ifstream infile("boarding_passes.txt");
  if (!infile) {
    cout << "can't open the file" << endl;
    exit(EXIT_FAILURE);
  }

  bool exists = false;
  while (getline(infile,line)) {
    if (line.find(seat) != string::npos) {
      exists = true;
      return line;
    }
  }
  if (exists == false) {
      return "Seat is unassigned.";
  }
}

// prints the name and seat of every passenger ordered by name or seat number in either ascending or descending order
void print_manifest(int i, vector <string> v) {
  vector <string> tempv;
  vector <string> result;
  switch (i) {
    case 1: {
      for (auto& row: v) {
        tempv.push_back(row.substr(row.find("Seat:") + 6, row.size()));
      }

      sort(tempv.begin(), tempv.end());

      for (auto& row1: tempv) {
        for (auto& row2: v) {
          if (row2.find(row1) != string::npos) {
            result.push_back(row2);
          }
        }
      }
    }
      break;
    
    case 2: {
      for (auto& row: v) {
        tempv.push_back(row.substr(row.find("Seat:") + 6, row.size()));
      }

      sort(tempv.begin(), tempv.end(), greater<string>());
      
      for (auto& row1: tempv) {
        for (auto& row2: v) {
          if ((row2.find(row1) != string::npos)) {
            result.push_back(row2);
          }
        }
      }
    }
    break;

    case 3: {
      sort(v.begin(), v.end());

      for (auto& row: v) {
        result.push_back(row);
      }
    }
    break;

    case 4: {
      sort(v.begin(), v.end(), greater<string>());

      for (auto& row: v) {
        result.push_back(row);
      }
    }
    break;

    default: {
      for (auto& row: v) {
        tempv.push_back(row.substr(row.find("Seat:") + 6, row.size()));
      }

      sort(tempv.begin(), tempv.end());

      for (auto& row1: tempv) {
        for (auto& row2: v) {
          if (row2.find(row1) != string::npos) {
            result.push_back(row2);
          }
        }
      }
    }
    break;
  }

  for (auto& row: result) {
    cout << row.substr(0, row.find("Seat:") + 8) << endl;
  }
}

// books a seat at the given row and column number and saves it
void book_seat(string filename, string &line, int row, int col) {
  line.at(((row - 1) * 19) + ((col - 1) * 2)) = '1';
  save_seats(filename, line);
}

//checks if the first class seats are full
string fc_full(int seats[][9], string &chart, string &bp){
  for(int i = 0; i <= 9; i++){

    int row = 1;
    int counter = 0;
    if(seats[row][i] == 1){
      counter++;
      if(counter == 9){
        cout << "Would you like to be put in the business class? Y/N";
        move_fcseat("seating.txt", chart, bp, seats);
      }
      else{
        return "";
      }
    }
  }
}

//checks if the business class seats are full
string bc_full(int seats[][9], string &chart, string &bp){
  for(int row = 2; row <= 3; row++){
    for(int col = 0; col <= 9; col++){
      int counter = 0;
      if(seats[row][col] == 1){
        counter++;
        if(counter == 9){
        cout << "Would you like to be put in the economy class? Y/N";
        move_bcseat("seating.txt", chart, bp, seats);
      }
        else{
            return "";
        }
    }
  }
    }
  }

//takes user input and moves them to business class depending on response
void move_fcseat(string filename, string &chart, string &bp, int seats[][9]){
  char c;
  cin >> c;
  bool avail = true;
  if(c == 'Y' || c == 'y'){
      while (bc_full(seats) == "") {
      int row = rand() % 3 + 1;
      int col = rand() % 9 + 1;
      if (row == 1 || (chart.at(((row - 1) * 19) + ((col - 1) * 2)) == '1')) {
        int row = rand() % 3 + 1;
        int col = rand() % 9 + 1;
      } 
      else {
        string fname;
        string lname;
        string seat = get_col(col) + to_string(row);
        string level = "Business Class";
        cout << "What is your first name?" << endl;
        cin >> fname;
        cout << endl;
        cout << "What is your last name?" << endl;
        cin >> lname;
        cout << endl;
        string name = fname + " " + lname;
        book_seat(filename, chart, row, col);
        load_seats("boarding_passes.txt", bp);
        add_bp(name, seat, level, bp);
        avail = false;
      }
    }
  }
  else if(c == 'N' || c == 'n'){
    cout << "Next flight leaves in 3 hours.";
  }
}

//takes user input and moves them to economy class depending on response
void move_bcseat(string filename, string &chart, string &bp, int seats[][9]){
  char c;
  cin >> c;
  bool avail = true;
  if(c == 'Y' || c == 'y'){
    while (avail) {
      int row = rand() % 5 + 4;
      int col = rand() % 9 + 1;
      if (chart.at(((row - 1) * 19) + ((col - 1) * 2)) == '1') {
        int row = rand() % 5 + 4;
        int col = rand() % 9 + 1;
      } else {
        string fname;
        string lname;
        string seat = get_col(col) + to_string(row);
        string level = "Economy";
        cout << "What is your first name?" << endl;
        cin >> fname;
        cout << endl;
        cout << "What is your last name?" << endl;
        cin >> lname;
        cout << endl;
        string name = fname + " " + lname;
        book_seat(filename, chart, row, col);
        load_seats("boarding_passes.txt", bp);
        add_bp(name, seat, level, bp);
        avail = false;
      }
    }
  }
  else if(c == 'N' || c == 'n'){
    cout << "Next flight leaves in 3 hours.";
  }
}

// Prompts the user for if they want to ride first class, business class, or economy class and assigns them their seat
void init_assignment(string filename, string &chart, string &bp, int seats[][9]) {
  vector <string> seat_rows;
  char c;
  cout << "Please type 'F' for 'first class'" << endl;
  cout << "Please type 'B' for 'business class'" << endl;
  cout << "Others will be 'economy class':" << endl;
  cin >> c;
  bool avail = true;
  

  if (c == 'F' || c == 'f') {
 

    while (fc_full(seats) == "") {
      int row = 1;
      int col = rand() % 9 + 1;
      if (chart.at(((row - 1) * 19) + ((col - 1) * 2)) == '1') {
        int row = 1;
        int col = rand() % 9 + 1;
      } else {
        string fname;
        string lname;
        string seat = get_col(col) + to_string(row);
        string level = "First Class";
        cout << "What is your first name?" << endl;
        cin >> fname;
        cout << endl;
        cout << "What is your last name?" << endl;
        cin >> lname;
        cout << endl;
        string name = fname + " " + lname;
        book_seat(filename, chart, row, col);
        load_seats("boarding_passes.txt", bp);
        add_bp(name, seat, level, bp);
        avail = false;
        }
    }
  } 
  else if (c == 'B' || c == 'b') {
    load_vector("seating.txt", seat_rows);

    while (bc_full(seats) == "") {
      int row = rand() % 3 + 1;
      int col = rand() % 9 + 1;
      if (row == 1 || (chart.at(((row - 1) * 19) + ((col - 1) * 2)) == '1')) {
        int row = rand() % 3 + 1;
        int col = rand() % 9 + 1;
      } else {
        string fname;
        string lname;
        string seat = get_col(col) + to_string(row);
        string level = "Business Class";
        cout << "What is your first name?" << endl;
        cin >> fname;
        cout << endl;
        cout << "What is your last name?" << endl;
        cin >> lname;
        cout << endl;
        string name = fname + " " + lname;
        book_seat(filename, chart, row, col);
        load_seats("boarding_passes.txt", bp);
        add_bp(name, seat, level, bp);
        avail = false;
      }
    }
  } 
  else {

    while (avail) {
      int row = rand() % 5 + 4;
      int col = rand() % 9 + 1;
      if (chart.at(((row - 1) * 19) + ((col - 1) * 2)) == '1') {
        int row = rand() % 5 + 4;
        int col = rand() % 9 + 1;
      } else {
        string fname;
        string lname;
        string seat = get_col(col) + to_string(row);
        string level = "Economy";
        cout << "What is your first name?" << endl;
        cin >> fname;
        cout << endl;
        cout << "What is your last name?" << endl;
        cin >> lname;
        cout << endl;
        string name = fname + " " + lname;
        book_seat(filename, chart, row, col);
        load_seats("boarding_passes.txt", bp);
        add_bp(name, seat, level, bp);
        avail = false;
      }
    }
  }
  }



// Controls all of the user interaction
void interact(int num, string filename, string &chart, int seats[][9]) {
  string bp;
  string seat;
  string fname;
  string lname;
  string new_name;
  string seat_edit;
  vector <string> manifest;
  
  while (true) {
    cin >> num;
    if (cin.fail() || num < 1 || num > 9) {
      cin.clear();
      cin.ignore();
      cout << "Enter a number from 1-9:" << endl;
    } else {
      break;
    }
  }

  //use while loop and then break when user presses 9
  switch (num) {
    case 1:
      load_seats("seating.txt", chart);
      load_vector("boarding_passes.txt", manifest);
      cout << "Seating and Manifest Loaded!";
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 2:
      load_seats("boarding_passes.txt", bp);
      save_seats("seating.txt", chart);
      save_seats("boarding_passes.txt", bp);
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 3:
      cout << "0 = available\n1 = filled\n";
      display(chart);
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 4:
      load_seats("seating.txt", chart);
      load_seats("boarding_passes.txt", bp);
      init_assignment(filename, chart, bp, seats);
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 5:
      cout << "What is your current seat?" << endl;
      cin >> seat_edit;
      cout << endl;
      load_vector("boarding_passes.txt", manifest);
      update(manifest, bp, seat_edit);
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 6:
      cout << "What is your first name?" << endl;
      cin >> fname;
      cout << endl;
      cout << "What is your last name?" << endl;
      cin >> lname;
      cout << endl;
      new_name = fname + " " + lname;
      cout << "What is your seat?" << endl;
      cin >> seat_edit;
      cout << endl;
      load_vector("boarding_passes.txt", manifest);
      cancel(manifest, bp, seat_edit, new_name);
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 7:
      cout << "What seat do you want a boarding pass for?" << endl;
      cin >> seat;
      cout << endl;
      cout << get_bp(seat) << endl;
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 8:
      int i;
      cout << "Choose one of the four available sorting options for your passenger manifest:" << endl;
      cout << "1. By seat number in ascending order" << endl;
      cout << "2. By seat number in descending order" << endl;
      cout << "3. Alphabetically by name from A-Z" << endl;
      cout << "4. Alphabetically by name from Z-A" << endl;
      cin >> i;
      cout << endl;
      load_vector("boarding_passes.txt", manifest);
      print_manifest(i, manifest);
      main_menu();
      interact(num, filename, chart, seats);
      break;
    case 9:
      exit(EXIT_SUCCESS);
    default:
      break;
  }
}