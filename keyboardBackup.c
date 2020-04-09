//#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Function Declarations: */
 
#define BOARD_SIZE 6

int piecesRemaining[BOARD_SIZE]; //keep track of the number of game pieces that still exist in each row
void resetMatch(bool * turn, bool * gameOver, char * continueGame, int * piecesRemaining, int row[BOARD_SIZE][BOARD_SIZE]);
bool removePieces(int rowNo, int noPieces, int row[BOARD_SIZE][BOARD_SIZE]);
bool checkWin();
void print(int row[BOARD_SIZE][BOARD_SIZE]);
int receivedInput();
void updateRounds(bool turn, int * playerOneScore, int * playerTwoScore);

int main() {
     //Initial setup
    int rowNo;
    int noPieces;
    int row[BOARD_SIZE][BOARD_SIZE];
    bool turn;
    bool gameOver;
    char continueGame;
    int playerOneScore = 0, playerTwoScore = 0; //initial scores

    resetMatch (&turn, &gameOver, &continueGame, piecesRemaining, row);

	
    while(continueGame == 'y' && !gameOver)
    {
     //   print(row);
        bool invalidMove = true;
        while(invalidMove){
            printf( "Player %d: Which row would you like to remove pieces from? \n ", ((turn) ? 1 : 2));
			rowNo = receivedInput();
            //scanf( "%d", &rowNo);
                
            printf( " Player %d: How many pieces would you like to remove from %d? \n ",((turn) ? 1 : 2), rowNo);
            noPieces = receivedInput();
            //scanf( "%d", &noPieces);
            
         //   invalidMove = removePieces(rowNo, noPieces ,row);

        }

    }
    //game finished or user exited
    
    if (continueGame != 'y')
        printf("User Exited Game");
    
    return 0;
        
} 
       
      
int receivedInput(){ 
  /* Declare volatile pointers to I/O registers (volatile means that IO load
  and store instructions will be used to access these pointer locations,
  instead of regular memory loads and stores) */
  volatile int * PS2_ptr = (int * ) 0xFF200100;
  int PS2_data, RVALID;
  char byte1 = 0, byte2 = 0, byte3 = 0;
  // PS/2 mouse needs to be reset (must be already plugged in)
  *(PS2_ptr) = 0xFF; // reset
	
	int letterCode; 
	bool inputFinished = false;
  while (!inputFinished) {
    PS2_data = * (PS2_ptr); // read the Data register in the PS/2 port
    RVALID = PS2_data & 0x8000; // extract the RVALID field

    if (RVALID) {
      /* shift the next data byte into the display */
      byte1 = byte2;
      byte2 = byte3;
      byte3 = PS2_data & 0xFF;
      if ((byte2 == (char) 0xAA) && (byte3 == (char) 0x00))
        // mouse inserted; initialize sending of data
        *(PS2_ptr) = 0xF4;
		unsigned int shift_buffer[3]; 
		 shift_buffer[2]= byte3;
	//printf("\nvalue is : %d", shift_buffer[2]);
		shift_buffer[1] = byte2;
	//printf("\nprev_value is : %d", shift_buffer[1]);
		shift_buffer[0] = byte1;
	//printf("\nprev2_value is : %d", shift_buffer[0]);
		
		if (byte1==90 && byte2==240 && byte3==90)
			inputFinished = true;
		else if (byte3 != 240 && byte3 != 90)
			letterCode = byte3;
    }
  }
	
	switch(letterCode) {//convert make code (in decimal) into key pressed
		case 69:
			return 0;
		case 22:
			return 1;
		case 30:
			return 2;
		case 38:
			return 3;
		case 37:
			return 4;
		case 46:
			return 5;
		case 54:
			return 6;
		case 61:
			return 7;
		case 62:
			return 8;
		case 70:
			return 9;
		default: //non-number key
			return -1;	
	}			
}    
     
        
void resetMatch(bool * turn, bool * gameOver, char * continueGame, int * piecesRemaining, int row[BOARD_SIZE][BOARD_SIZE]){
    
    *turn = true;
    *gameOver = false;
    *continueGame = 'y';
    
    //Randomize the distibution of the 21 pieces across the piles
    int totalCount = 21;
    //initliaze the # of game pieces in each row
    int randomNumber;
    for (int i = 0; i < BOARD_SIZE && totalCount > 0; i++){
        randomNumber = rand()%7; //random number from 0 to 6
        piecesRemaining[i] = randomNumber; 
        totalCount-=randomNumber;
    }

    //for each board's row, set the correct number of pieces 
    for (int i = 0; i < BOARD_SIZE;i++)
    {
        for(int j = 0; j < piecesRemaining[i]; j++)
        {
            row[i][j] = 1;
        }
    }
    
    for (int i = 0; i < BOARD_SIZE;i++)
    {
        for(int j = piecesRemaining[i]; j < BOARD_SIZE; j++)
        {
            row[i][j] = 0;
        }
    }
    
}
           
    
    
    

    


