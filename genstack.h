/** genstack.h
 *Header file for Delimiter syntax checker
 *@author Mary Kate Crittenden
 *2278514
 *critt102@mail.chapman.edu
 *CPSC 350-01
 *Assignment 3
 */
#include <iostream>
#include <fstream>
using namespace std;
/**
 * The class life is a template class, that sets up the functions for a stack,
 * and implements the functions pop, push, peek, isEmpty, isFull, and testDel.
 */
template <class T>
class GenStack{
  public:
    //size of stack
    int size;
    //position of top of stack
    int top;
    //read a file in to analyze
    ifstream in_file;
    //current line
    string line;
    //array based stack
    T *genArray;
    //stack used for allocating more space to genArray
    T *newArray;
    //current line number of file being analyzed
    int line_num=0;
    //constructor
    GenStack()
    {
      genArray=new T[10];
      size=10;
      top =-1;
      line="";
    }
    //overloaded constructor
    GenStack(int initSize)
    {
      genArray=new T[initSize];
      size=initSize;
      top=-1;
      line="";
    }
    //destructor
    ~GenStack()
    {
      delete genArray;
    }
    /**
     * Adds item to the stack
     * @param d a template item, represents the item to be stored
     */
    void push(T d){
      //if stack is full, more room needs to be allocated
      if(top>=size-1){
        newArray=new T[size];
        //go through entire genArray stack and copy to newArray
        while(top!=-1){
          newArray[top]=genArray[top];
          --top;
        }
        delete genArray;
        //allocate a new array of twice the size for the genArray stack
        genArray=new T[size*2];
        //copy contents of newArray back to genArray
        while(top<size-1){
          ++top;
          genArray[top]=newArray[top];
        }
        //change variable size to reflect new size of genArray
        size=size*2;
        delete newArray;
      }
      //push item to stack
      genArray[++top]=d;
    }
    /**
     * Removes item from the top of the stack
     * @return T, a template item
     */
    T pop(){
      //error checking, make sure it's not isEmpty
      if(isEmpty()==false){
        return genArray[top--];
      }
    }
    /**
     * Looks to see what item is at the top of the stack without removing the item
     * @return T, the template item at the top of the stack
     */
    T peek(){
      //check if empty
      return genArray[top];
    }
    /**
     * Checks if the stack/array is full
     * @return bool, true if stack is full
     */
    bool isFull(){
      return (top==size-1);
    }
    /**
     * Checks if the stack/array is empty
     * @return bool, true if stack is empty
     */
    bool isEmpty(){
      return (top==-1);
    }
    /**
     * Analyzes a file and checks for correct Delimiters
     * @param fileName, the name of the file to be analyzed
     */
    void testDel(string fileName){
      line_num=0;
      in_file.open(fileName, ios::in);
      //if file does not exist
      if(in_file.is_open()==false){
        cout<<"File not found. Try again."<<endl;
        exit(0);
      }
      while(in_file.is_open()){
        //read file line by line
        while(getline(in_file, line)){
          line_num++;
          //read file character by character
          for(int i=0; i<line.size();++i){
            if(line[i]=='(' || line[i]=='{' || line[i]=='['){
              push(line[i]);
            }
            else if(line[i]==')'){
              if(genArray[top]=='('){
                pop();
              }
              else{
                if(genArray[top]=='{'){
                  cout<<"Line "<<line_num<<", expected '}' found ')'"<<endl;
                  exit(0);
                }
                else if(genArray[top]=='['){
                  cout<<"Line "<<line_num<<", expected ']' found ')'"<<endl;
                  exit(0);
                }
                else{
                  cout<<"Extra ')' found at line "<<line_num<<endl;
                  exit(0);
                }
              }
            }
            else if(line[i]=='}'){
              if(genArray[top]=='{'){
                pop();
              }
              else{
                if(genArray[top]=='('){
                  cout<<"Line "<<line_num<<", expected ')' found '}'"<<endl;
                  exit(0);
                }
                else if(genArray[top]=='['){
                  cout<<"Line "<<line_num<<", expected ']' found '}'"<<endl;
                  exit(0);
                }
                else{
                  cout<<"Extra '}' found at line "<<line_num<<endl;
                  exit(0);
                }
              }
            }
            else if(line[i]==']'){
              if(genArray[top]=='['){
                pop();
              }
              else{
                if(genArray[top]=='('){
                  cout<<"Line "<<line_num<<", expected ')' found ']'"<<endl;
                  exit(0);
                }
                else if(genArray[top]=='{'){
                  cout<<"Line "<<line_num<<", expected '}' found ']'"<<endl;
                  exit(0);
                }
                else{
                  cout<<"Extra ']' found at line "<<line_num<<endl;
                  exit(0);
                }
              }
            }
          }
        }
        while(top>-1){
          if(genArray[top]=='{'){
            cout<<"Reached end of file, missing: '}'"<<endl;
            exit(0);
          }
          else if(genArray[top]=='('){
            cout<<"Reached end of file, missing: ')'"<<endl;
            exit(0);
          }
          else if(genArray[top]=='['){
            cout<<"Reached end of file, missing: ']'"<<endl;
            exit(0);
          }
          top--;
        }
        in_file.close();
      }
    }
};
