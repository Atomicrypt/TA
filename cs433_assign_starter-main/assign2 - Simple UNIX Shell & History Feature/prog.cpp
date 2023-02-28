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
// test
/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[])
{
    // TODO: implement this function

    pid_t pid;   // process id type, process id
    pid = fork();  // fork a child process

    if (pid < 0) {  // error case
      fprintf(stderr, "Fork failed");
      return 1;
    }
    else if (pid == 0)
    {   // child process

      // list files/directories if command is "ls"
      if (command[0] != 'l' || command[1] != 's') {
        printf("unrecognized command\n");
      }
      else {
        execlp("/bin/ls","ls",NULL);  // execute "ls" command 
      }
    }
    else {  // parent process waits for next command
      wait(NULL);
    }

    int count = 0; // index for each char of the command line argument
    char *token = strtok(command, " "); // creates array of spaces for command line arg

    while (token != NULL && count != 50) { 
      if (*token == '<') { // checks if char token is '<'
        int out = open(strtok(NULL, " "), O_WRONLY | O_TRUNC | O_CREAT, 0600);
        dup2(out, 1);
        close(out);
      }
      else if (*token == '>') { // checks if token is '>'
        int in = open(strtok(NULL, " "), O_RDONLY);
        dup2(in, 0);
        close(in);
      }
      else if (*token == '|') { // checks if token is '|'
      }
      else if (*token == '&') { // checks if token is '&'
      }
      else {
        args[count] = token;  // argument at index gets token
      }
      count++;
    }
    token = strtok(NULL, " "); // read each token that isn't a space
    return 0;
}

// TODO: Add additional functions if you need

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */

    // TODO: Add additional variables for the implementation.
    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);
        // Parse the input command
        int num_args = parse_command(command, args);

        // TODO: Add your code for the implementation
        /**
         * After reading user input, the steps are:
         * (1) fork a child process using fork() #########CURRENT#########
         * (2) the child process will invoke execvp()2
         * (3) parent will invoke wait() unless command included &
         */

    }
    return 0;
}