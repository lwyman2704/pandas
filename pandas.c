//********************************************************
// pandas.c
// Author: Lorenzo Wyman
// 
// Date: 10/11/24
// 
// Purpose: This program prints a specific message to the
// terminal if the file does/does not exist, the name of 
// the file and its contents aswell as a sample from the file
// that is >= 6 characters.
// Input: None
//
// Output: (to the command line) If the arguments is T/F, 
// file name, file existance T/F, contents of file(s) and
// sample from file.
// //********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkArguments(int numOfArguments, char **cmdLineArguments){

    if (numOfArguments >= 2){
        printf("\n");
       printf("Arguments: true\n");
    } else {
        printf("Arguments: false\n");
    }
        return 1;
}

char *charlessFileName (char *fileName){

    char *charlessName = strrchr(fileName, '/');

    return (charlessName != NULL) ? charlessName + 1 : fileName;
}

int printFileNames(int numberOfFiles, char **fileNames){

    for (int i = 1; i < numberOfFiles; i++){             
        char *defaultFilename = charlessFileName(fileNames[i]);       //start i at 1 so it does not print the name of the file that we are on currently
         printf("File Name: %s\n", defaultFilename);
    }

    return 1;
}

int checkFileExists(char *fileName){

    FILE *reader = NULL;
    reader = fopen(fileName, "r");                              //we need to open the file in read mode

    if (reader != NULL){        
        printf("\n");                                // if the file exists, it will output true and then we close the file after to avoid a segfault.
        printf("File Exists: true\n"); 
        fclose(reader);
        return 1;

    } else {
        printf("\n");
        printf("File Exists: false\n");
    }

    return 1;
}

int readFile(char *fileName){

    FILE *reader = fopen(fileName, "r");

        if (reader == NULL) {
            printf("Cannot read because of missing file: %s\n", fileName);
            return 0;                                          // Stops if the file cannot be opened
    }

    char stringArray[100];                                     //initialize the size of the stringArray

    while (fgets(stringArray, sizeof(stringArray), reader) != NULL) {   //fgets is going to be able to access the file contents then sizeof will look at the size of stringArray
        printf("Name: %s", stringArray);                       // this outputs the content 
    }
    printf("\n");
    fclose(reader);                                           // this has to be used to close the file after reading to avoid segfaults
    return 5;
}

int extractSample(char *fileName) {

FILE *reader = fopen(fileName, "r");

    if (reader == NULL) {
        printf("Sample not found because of missing file: %s\n", fileName);
        return 0;                                             // Exit if the file cannot be opened
    }

    char word[100];                                            //initialize a word variable so we can analyze the words within the file and then see if they are more than 6 characters long
    int line = 1;                                             // inititialize a line variable so that we can also iterate or keep track of which line we are on.
    
    while (fscanf(reader, "%s", word) != EOF) {              //while the contents are being read as long as you havent reached the end of the file
        if (strlen(word) >= 6) {                             //if the length of the string is >= 6                          
            printf("Sample %d: %s\n", line, word);
            line++;
        }      
    
    }
    
    fclose(reader); 
    return 5;
}


int main(int argc, char **argv){

    if (argc < 4) {                                       //if the amount of arguments are less than 2 it will provide this error
                         
        printf("There are not atleast 2 arguments.\n");
        return 1;
    }

    checkArguments(argc, argv);
                                                      
    for (int i = 1; i < argc; i++) {                     //this loop allows for the program to loop thorough each argument, which are the files instead of only the first

    char *fileName = argv[i];

        checkFileExists(fileName);
        printf("File Name: %s\n", charlessFileName(fileName));
        readFile(fileName);
        extractSample(fileName);

    }
  return 0;
}
