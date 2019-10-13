/** genstack.h
 *Main file for Delimiter syntax checker
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 3
 */
#include "genstack.h"
#include <iostream>
#include <fstream>
using namespace std;
/**
 * main method, implemetns and runs genstack.h
 * @param  argc numer of arguments
 * @param  argv command lines arguments
 * @return 0 to end main call
 */
int main(int argc, char**argv) {
  //used to see if user wants to analyze another file
  bool again=true;
  //stores input of user when prompted about analyzing another file
  char yn;
  //used in while loop to check for user input about analyzing another file
  int in_check=0;
  //stores name of file to be analyzed
  string next_file;

  GenStack<char> test(10);
  test.testDel(argv[1]);

  //loop to continue prompting user for input about analyzing another file
  while(in_check==0){
    cout<<endl;
    cout<<"Delimiter syntax for given file is correct."<<endl;
    cout<<"Would you like to analyze another file? y or n?"<<endl;
    cin>>yn;
    //if no
    if(yn=='n' || yn=='N'){
      again=false;
      in_check=1;
    }
    //if yes
    else if(yn=='y' || yn=='Y'){
      again=true;
    }
    //if input is invalid
    else{
      cout<<"Input entered is invalid. Please try again."<<endl;
      exit(0);
    }
    //if yes, ask for name of file, then analyze said file
    if(again==true){
      cout<<"Enter the name of the file you wish to analyze."<<endl;
      cin>>next_file;
      test.testDel(next_file);
    }
  }
  return 0;
}
