#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

const string IN_FILE_NAME = "input.txt";
const int MAX_CREATURES = 5;
const int strengthCeiling = 176, strengthFloor = 75, healthCeiling = 151, healthFloor = 50;

void checkInputFile();
void exitProgram();
void invalidInput();
void printCreatures();
void printDamage();
void printMenuChoices();
void switchStatement();
void updateCreaturesWithOutput();
void updateCreaturesWithoutOutput();
int validateInput(string input);

enum MenuOptions {
  PRINTCREATURE = 1,
  UPDATECREATURES = 2,
  PRINTDAMAGE = 3,
  EXITPROGRAM = 4
};

class myCreature{
  private:
    int strength = 0;
    int health = 0;
    string id = "";

  public:
    myCreature() {
      strength = rand() % strengthCeiling + strengthFloor;
      health = rand() % healthCeiling + healthFloor;
      id = "Hello World";
    }

    myCreature(int s, int h, int i) {
      strength = s;
      health = h;
      id = i;
    }

    void setCreature(string newId) {
      strength = rand() % strengthCeiling + strengthFloor;
      health = rand() % healthCeiling + healthFloor;
      id = newId;
    }

    const int getStrength() { return strength; }
    const int getHealth() { return health; }
    const string getId() { return id; }
    const int getDamage() { return (rand() % strength) + 1; }

    string creatureAsString(){
      stringstream ss;
      ss << "|" << right << setw(12) << setfill(' ') << getId() << "|" 
         << right << setw(12) << setfill(' ') << to_string(getStrength()) << "|" 
         << right << setw(12) << setfill(' ') << to_string(getHealth()) << "|";
      
      // cout << " number: "  << right << setw(7) << 24; // DELETE ME
      return ss.str();
    }
};

myCreature creatures[MAX_CREATURES];

int main(){
  srand(time(0));

  updateCreaturesWithoutOutput();
  printMenuChoices();

  switchStatement();
}

void switchStatement(){
  int userInput;

  do{
    string stringUserInput;
    getline(cin, stringUserInput);
    userInput = validateInput(stringUserInput);

    cout << "\n";

    switch(userInput){
      case (PRINTCREATURE):
        printCreatures();
        break;

      case (UPDATECREATURES):
        updateCreaturesWithOutput();
        break;

      case (PRINTDAMAGE):
        printDamage();
        break;

      case (EXITPROGRAM):
        exitProgram();
        break;
      
      default:
        invalidInput();
        break;
    }
  } while (userInput != 5);
}

void printCreatures(){
  stringstream tableHeading;
  stringstream tableFooter;

  tableHeading << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(15) << "|\n|"
     << setfill('-') << setw(7) << "ID" << setfill('-') << setw(6) << "|"
     << setfill('-') << setw(9) << "HEALTH" << setfill('-') << setw(4) << "|"
     << setfill('-') << setw(10) << "STRENGTH" << setfill('-') << setw(4) << "|\n"
     << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|";
  
  tableFooter << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(15) << "|\n\n";

  cout << tableHeading.str() << "\n";

  for (int i = 0; i < MAX_CREATURES; i++){
    cout << creatures[i].creatureAsString() + "\n";
  }

  cout << tableFooter.str();

  printMenuChoices();
  switchStatement();
}

void updateCreaturesWithOutput(){
  checkInputFile();
  ifstream inFile; 
  inFile.open(IN_FILE_NAME); 

  string idList[MAX_CREATURES];
  int count = 0;

  while(count < MAX_CREATURES && getline(inFile, idList[count])){
    count++;
  }

  inFile.close();

  for (int i = 0; i < MAX_CREATURES; i++){
    creatures[i].setCreature(idList[i]);
  }

  cout << "Creature Stats Randomly Updated\n";
  printCreatures();

  printMenuChoices();
  switchStatement();
}

void updateCreaturesWithoutOutput(){
  checkInputFile();
  ifstream inFile; 
  inFile.open(IN_FILE_NAME); 

  string idList[MAX_CREATURES];
  int count = 0;

  while(count < MAX_CREATURES && getline(inFile, idList[count])){
    count++;
  }

  inFile.close();

  for (int i = 0; i < MAX_CREATURES; i++){
    creatures[i].setCreature(idList[i]);
  }

  printMenuChoices();
  switchStatement();
}

void printDamage(){
  stringstream tableHeading;
  stringstream tableFooter;

  tableHeading << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(15) << "|\n|"
     << setfill('-') << setw(7) << "ID" << setfill('-') << setw(6) << "|"
     << setfill('-') << setw(9) << "HEALTH" << setfill('-') << setw(4) << "|"
     << setfill('-') << setw(10) << "STRENGTH" << setfill('-') << setw(3) << "|"
     << setfill('-') << setw(9) << "DAMAGE" << setfill('-') << setw(5) << "|\n"
     << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|";

  tableFooter << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(13) << "|" << setfill('-') << setw(15) << "|\n\n";

  cout << tableHeading.str() << "\n";

  for (int i = 0; i < MAX_CREATURES; i++){
    stringstream damageSection;

    damageSection << right << setw(12) << setfill(' ') << creatures[i].getDamage() << "|\n";

    cout << creatures[i].creatureAsString();
    cout << damageSection.str();
  }

  cout << tableFooter.str();

  printMenuChoices();
  switchStatement();
}

void exitProgram(){
  cout << "Exiting Program";
}

void checkInputFile(){
  ifstream inFile; 

  inFile.open(IN_FILE_NAME); 

  if(!inFile){
    cout << "Failed reading input file. Terminating program\n";

    system("pause");
    exit(EXIT_FAILURE);
  }
  inFile.close();
}

void invalidInput(){
  cout << "- Invalid input, please try again. - \n";
 
  printMenuChoices();
}

void printMenuChoices(){
  cout << setfill('-') << setw(100) << " " << "\nHere are your choices (input the number for the corresponding action): \n1. Print list of creatures and their stats. \n2. Update creatures, randomly setting health, strength, and id. \n3. Print damage for all creatures along side their stats. \n4. Exit."
       << endl;
}

int validateInput(string input){
  if(input.length() != 1){
    // returns 5 in order to result in default in switch statement
    return 5; 
  } else{
    return stoi(input);
  }
}

