/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Alex Nelson, Tyler Felicidario
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


using namespace std;
/*The maximum length command*/
#define MAX_LINE 80 
#define MAX_HISTORY 100 // The maximum number of commands to be stored in history

/**
 * @brief Class to access history based on previous command inputs
 */
class history {
  private:
    char *log[MAX_HISTORY] = {}; // History log
    int count; // The current number of elements in the log

    /**
     * @brief When the history overflows, replace the old commands
     */
    void shiftLog() {
        // Shift the log to erase older commands
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            log[i] = log[i + 1];
        }
    }

  public:
    
    // Default constructor
    history() { 
      count = 0;
    }

    /**
     * @brief Adds to the history
     *
     * @param args command line arguments
     * @param num_args  number of arguments
     */
    void add(char *args[], int num_args) {
        if (count == MAX_HISTORY) { // If the number of elements is greater than history, need to shift the array
            shiftLog();
            count--; // Decrement the count so that it can be added to the last index
        }
        char command[MAX_LINE] = {};
        strcat(command, args[0]); // Append the command (no space)
        for (int i = 1; i <= num_args; i++) { // <= since numberOfArgs excludes the command
            strcat(command, " "); // Add a space
            strcat(command, args[i]); // Append the arguments 
        }
        // Combine the args
        log[count] = strdup(command); // Set the log
        count++;   // Increment the count
    }

    /**
     * @brief Function clears the history
     */
    void clear() {
        for (unsigned int i = 0; i < MAX_HISTORY; i++) {
            log[i] = NULL;
        }
        count = 0;
    }

    /**
     * @brief Returns the previous command
     */
    char *previous() {
        if (count == 0) {
            cout << "Shell history empty" << endl;
            return NULL; // history is empty
        }
        return log[count - 1];
    }
    /**
     * @brief Displays the commands (oldest at the top to most recent at the bottom)
     */
    void display() {
        // Iterate through log
        if (count == 0) {
            cout << "History is empty." << endl;
            return;
        }
        for (unsigned int i = 0; i < count; i++) {
            cout << i + 1 << ": " << log[i] << endl;
        }
    }
};

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command command line
 * @param args command line arguments
 * @return int
 */
int parse_command(char command[], char *args[])
{
    // TODO: implement this function

    int count = 0; // index for each char of the command line argument
    char *token = strtok(command, " "); // creates array of spaces for command line arg
    //place args into args array
    while (token != NULL) { //while accepting tokens
      args[count++] = token;  //first command
      token = strtok(NULL, " "); //get the rest of the args
    }
    args[count] = NULL; //terminate end of array
    args[count - 1] = strtok(args[count - 1], "\n");  //remove trailing new line from last arg
    return count - 1; //include all but command at index 0
}

/**
 * @brief check if argument is I/O
 *
 * @param args command line arguments
 * @param num_args number of arguments
 * @param type IO type
 * @return true/false
 */
bool checkIO(char *args[], int num_args, char &type){
for(int i = 0; i <= num_args; i++){
  if(strcmp(args[i], ">") == 0){
    type = 'o'; //o for output, writing to file
    return true;
  }
  else if(strcmp(args[i], "<") == 0){
    type = 'i'; //i for input, read from file
    return true;
  }
}
  return false;
}

/**
 * @brief check if argument is ampersand
 *
 * @param args command line arguments
 * @param num_args number of arguments
 * @return true/false
 */
bool checkAmp(char *args[], int num_args){
  for(int i = 0; i <= num_args; i++){
    if(strcmp(args[i], "&") == 0){
      return true;
    }
  }
  return false;
}

/**
 * @brief check if argument is pipe
 *
 * @param args command line arguments
 * @param num_args number of arguments
 * @return true/false
 */
bool checkPipe(char *args[], int num_args){
  for(int i = 0; i <= num_args; i++){
    if(strcmp(args[i], "|") == 0){
      return true;
    }
  }
  return false;
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */

    history shellHistory = history();

    while (should_run) {
      printf("osh>");
      fflush(stdout); // clears output buffer and prints everything
      // Read the input command
      char * userInput = fgets(command, MAX_LINE, stdin); //get user input
      if(strcmp(userInput, "\n") == 0) {  //enter button is pushed, do nothing
        continue; 
      }
      // Parse the input command
      int num_args = parse_command(command, args);

      if(strcmp(args[0], "exit") == 0){ //exit program
        should_run = false;
        return 0;
      } else if(strcmp(args[0], "history") == 0){
        shellHistory.display();
        continue;
      } else if(strcmp(args[0], "!!") == 0){
        char * prevCmd = shellHistory.previous(); //get history if it exists
        if(prevCmd == NULL){
          continue;
        }
        //run previous command
        strcpy(userInput, prevCmd);
        strcat(userInput, "\n");  //add newline for parse command function
        num_args = parse_command(command, args);  //repeat parse command function
      }

      shellHistory.add(args,num_args);

      pid_t pid = fork(); //create child process
      int fileDescriptor;

      if (pid < 0)
      {  // error case
        fprintf(stderr, "Fork failed");
        exit(1);
      }
      else if (pid == 0)
      {   // child process
        char ioType = ' ';  //empty char initializer
        if(checkIO(args,num_args, ioType)){ //check for ">" or "<" in argument array
          if(num_args == 1){
            printf("missing file argument\n");
            exit(1);
          }
          //redirect output to newly created file if one does not exist already
          if(ioType =='o'){ 
            fileDescriptor = open(args[num_args], O_WRONLY|O_CREAT, 0777);
          } else  //ioType is input
          { 
            fileDescriptor = open(args[num_args], O_RDONLY);
          }
          //removal of IO char and output file since its already open
          args[num_args - 1] = NULL;
          args[num_args] = NULL;
          //open file of the specified file descriptior
          dup2(fileDescriptor, ioType = 'o');
        }
        //successful process should return 0, else -1
        int procStatus = execvp(args[0], args);
        if(procStatus == -1){
          printf("Command not found\n");
        }
        exit(0);
      }
      else{
        wait(NULL);
      }
      
      //**
      // * After reading user input, the steps are:
      // * (1) fork a child process using fork() #########DONE#########
      // * (2) the child process will invoke execvp() #########DONE#########
      // * (3) parent will invoke wait() unless command included &  #########DONE#########
      // *

    }
    return 0;
}
