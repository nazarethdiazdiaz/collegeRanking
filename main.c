/* 
 CIS 26B: Homework 1B
 ********************
 NAME: Nazareth Diaz
 IDE (compiler): Replit
 *************************************************************************
    Arrays, Strings, Structures, Pointers, Functions and Files
    This program provides information about two-tear colleges in California.

 Suggested Design #1
 main calls the following functions:
   - readFile
   - insertionSort
   - printRange
   - writeFile

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64
#define INPUT_SIZE 100
#define FLUSH while( getchar()!= '\n')

typedef struct
{
    int rank;
    char name[NAME_SIZE];
    int year;
    int numStud;
}COLLEGE;

void readFile(const char inFileName[], COLLEGE list[], int *count);
void insertionSort(COLLEGE list[], int count);
void printRange(const COLLEGE list[], int count);
void writeFile(const char outFileName[], const COLLEGE list[], int count);

int main( void )
{
    COLLEGE collegeData[INPUT_SIZE];
    char inFileName[NAME_SIZE] = "in.txt";
    char outFileName[NAME_SIZE] = "out.txt";
    int count; // actual number of colleges

    readFile(inFileName, collegeData, &count);
    insertionSort(collegeData, count);
    writeFile(outFileName, collegeData, count);
    printRange(collegeData, count);
    


    return 0;
}

/*******************************
Parameters: string inFileName, struct COLLEGE array, pointer to count 
Returns: void 
Readfile function reads the file in.txt, opens it, and writes in the data 
into the list array. Array of COLLEGE structures is now filled with data from file. 
  *******************************/
void readFile(const char inFileName[], COLLEGE list[], int *count)
{
  FILE *fpData;
  fpData = fopen(inFileName, "r");
  if(fpData == NULL)
  {
    printf("Error opening %s ", inFileName);
    printf("for reading\n");
    exit(101);
  }
  else
  {

    //get number of college count 
    int c;
    for(c = getc(fpData); c !=EOF; c = getc(fpData))
      {
        if(c == '\n')
          *count = *count + 1;
      }
    

    rewind(fpData);

    int ch;
    int i = 0;

    //reading data from file
    while(i < *count)
      {

        fscanf(fpData, "%d %64[^;]%*c %d %d", &list[i].rank,     
            list[i].name, &list[i].year, &list[i].numStud);
      
        i++;


      }
    
  }
}
/***************************
Parameters: COLLEGE type array, int count 
Returns: void
This function uses the insertion sort algorithm to sort the 
list array in ascending order of college ranking number. 
****************************/

void insertionSort(COLLEGE list[], int count)
{

  int curr, walk;

  for(int curr = 1; curr < count ; curr++)
    {
      COLLEGE temp = list[curr];
      walk = curr - 1;

      while(walk >= 0 && temp.rank < list[walk].rank ){
        list[walk + 1] = list[walk];
        walk--;
        
        
        
      }
      list[walk + 1] = temp;

      
    }
}
/***************************
Parameters: string outFileName, pointer to COLLEGE array, int count 
This function takes the COLLEGE list array and writes out all the colleges
in ascending order of ranking to out.txt file. 
 **************************/

void writeFile(const char outFileName[], const COLLEGE list[], int count)
{
  FILE *fpOut = fopen(outFileName, "w");
  int i = 0;
  while(i < count)
    {    
      fprintf(fpOut, "%d %s %d %d\n", list[i].rank, list[i].name, list[i].year,       
        list[i].numStud);
      i++;
    }

  //closing file
  int closeCheck;
  closeCheck = fclose(fpOut);
  if(closeCheck == EOF)
  {
    printf("Error closing %s!", outFileName);
    exit(201);
  }
}
/*************************
This function takes in const COLLEGE list array and int count.
It asks the use to enter two numbers in consecutive order y their ranking. 
The colleges matching user input will be displayed to screen.
*************************/

void printRange(const COLLEGE list[], int count)
{
  int usrOne, usrTwo;
  do{
    printf("Enter consecutive number of schools to be displayed: \n");
    scanf("%d %d", &usrOne, &usrTwo);
    if((usrOne >= 1 && usrOne <= 14) && (usrTwo >= 2 && usrTwo <= 15))
    {
      // code to display user selection
      printf("Displaying colleges selected:\n");
      for(int i = usrOne; i <= usrTwo; i++)
        {
          printf("%d %s %d %d\n", list[i-1].rank, list[i-1].name, list[i-1].year, 
            list[i-1].numStud);
        }
    }
  }while(!(usrOne == 0 && usrTwo == 0));
  
}
