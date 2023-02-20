// Header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

// Defined sizes/ lengths
#define MAX_LINE_LENGTH 80
#define MAX_ROWS 60
#define MAX_COLS 60
#define MAX_GENERATIONS 252

// Method declarations
void printUniverse(int curr);
void readUniverse(void);
int Game(void);
void GameRules(int x, int y, int isAlive);
int getNeighbors(int x, int y);
int cycleTest(int i);
void restartGame(void);

// Global variables
int rows;
int cols;
int currGeneration = 0;

char currLine[MAX_LINE_LENGTH];

// A struct for  initiating a universe(generation)
typedef struct universe{
    char map[MAX_ROWS][MAX_COLS];
}universe;

// An array for holding all generations of a case
universe generations[MAX_GENERATIONS];


// A main driver method that calls all other methods to actually simulate the game
int main(void) {
    int eof = getc(stdin);
    while (eof != EOF)  
    { 
        readUniverse();
        Game();
        restartGame();
        eof = getc(stdin); 
    } 
    return 0;
}


// A method that plays the game
int Game(void) {

    int cycleFound = 0;
    while(cycleFound==0){   
        for(int x=0; x<rows; x++) {
            for(int y=0; y<cols; y++) {
                if(generations[currGeneration].map[x][y]=='X') {
                    GameRules(x,y,1);
                }else{
                    GameRules(x,y,0);
                }
            }
        }

        //TODO Mbatwsalsh l8ayet 250
        currGeneration++;
        if(currGeneration>MAX_GENERATIONS-2){
            printf("No cycle was found!\n");
            break;
        }
        
        int i;
        for(i=0; i<currGeneration-1; i++){
            cycleFound = cycleTest(i);
            if(cycleFound == 1){
                printf("Found a cycle between generation %d and generation %d\n",i,currGeneration-1);
                break;
            }
        }
    }
    
    int z;
    for(z=0 ; z<currGeneration; z++){
        printUniverse(z);
    }
        
}


// Method for executing game rules
void GameRules(int x, int y, int isAlive){
    int neigborsCount = getNeighbors(x,y);
    
    if(isAlive==1){

        if(neigborsCount == 2 || neigborsCount == 3){
            generations[currGeneration+1].map[x][y] = 'X';
        } else{
            generations[currGeneration+1].map[x][y] = '.';
        }
    } 
    
    else{
        if(neigborsCount == 3){
            generations[currGeneration+1].map[x][y] = 'X';
        } else{
            generations[currGeneration+1].map[x][y] = '.';
        }
    }

}


// Method for detecting neighbours 
int getNeighbors(int x, int y){
    int neighbors = 0;

    // Top
    if((x-1) >= 0 && generations[currGeneration].map[x-1][y] == 'X'){
            neighbors++;
    }

    // Bottom
    if((x+1) < rows && generations[currGeneration].map[x+1][y] == 'X'){
        neighbors++;
    }

    // left
    if((y-1) >= 0 && generations[currGeneration].map[x][y-1]== 'X'){
        neighbors++;
    }
    
    // Right
    if((y+1) < cols && generations[currGeneration].map[x][y+1] == 'X'){
        neighbors++;
    }

    //Top right
    if((y+1) < cols && (x-1) >= 0 && generations[currGeneration].map[x-1][y+1] == 'X'){
        neighbors++;
    }

    // Top left
    if((y-1) >= 0  && (x-1) >= 0 && generations[currGeneration].map[x-1][y-1] == 'X'){
        neighbors++;
        
    }

    // Bottom right
    if((y+1) < cols && (x+1) < rows && generations[currGeneration].map[x+1][y+1] == 'X'){
        neighbors++;
        
    }

    // Bottom left
    if((y-1) >= 0  && (x+1) < rows && generations[currGeneration].map[x+1][y-1] == 'X'){
        neighbors++;
        
    }

    return neighbors;
}


// Method that checks for a cycle between generations
int cycleTest(int i){
    int flag = 1;
    for(int x=0; x<rows; x++) {
        for(int y=0; y<cols; y++) {
            if( generations[i].map[x][y] != generations[currGeneration].map[x][y]){
                flag = 0; 
            }
        }
    }
    return flag;
}


// Method to read a universe from the redirected text file
void readUniverse(void) {
    
    fgets(currLine, MAX_LINE_LENGTH, stdin);
    printf("*%s", currLine);
    
    fgets(currLine, MAX_LINE_LENGTH, stdin);
    char *sizeChar = strtok(currLine, " ");
    rows = atoi(sizeChar);
    sizeChar = strtok(NULL," ");
    cols = atoi(sizeChar);

    for(int i=0; i<rows; i++) {
        fgets(currLine, MAX_LINE_LENGTH, stdin);
        for(int j=0; j<cols; j++) {
            if(currLine[j]=='X') {
                generations[0].map[i][j] = 'X';
            }
            else{
                generations[0].map[i][j] = '.';
            }
        }
    }
}


// Method for printing the current generation of a universe with borders 
void printUniverse(int curr){
    printf("Generation: %d\n",curr);
    
    printf("+");
    for(int i=0;i<cols;i++){printf("-");}
    printf("+\n");

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {
            if(generations[curr].map[i][j] == 'X') {
                generations[curr].map[i][j] = '*';
            }
        }
    }

    for(int i=0; i<rows; i++) {
        printf("|");
        for(int j=0; j<cols; j++) {
            printf("%c",generations[curr].map[i][j]);
        }
        printf("|\n");
    }

    printf("+");
    for(int i=0;i<cols;i++){
        printf("-");
    }
    printf("+\n");
}

// Method for resetting everything before moving on to a new case 
void restartGame() {
    currGeneration = 0;
    int i;
    int x;
    int y;
    for(i=0; i<MAX_GENERATIONS; i++) {
        for(x=0; x<rows; x++) {
            for(y=0; y<cols; y++) {
                generations[i].map[x][y] = ' ';
            }
        }
    }
}
