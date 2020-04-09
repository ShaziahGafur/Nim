volatile int pixel_buffer_start; // global variable
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Function Declarations: */

#define BOARD_SIZE 6

//Game Logic Functions	
int piecesRemaining[BOARD_SIZE]; //keep track of the number of game pieces that still exist in each row
void resetMatch(bool * turn, bool * gameOver, bool * continueGame, int * piecesRemaining, int row[BOARD_SIZE][BOARD_SIZE]);
bool removePieces(int rowNo, int noPieces, int row[BOARD_SIZE][BOARD_SIZE]);
bool checkWin();
void print(int row[BOARD_SIZE][BOARD_SIZE]);
void printGameGrid();
int receivedInput();
void updateRounds(bool turn, int * playerOneScore, int * playerTwoScore);
bool proceedGame() ;

//VGA Functions
void printPieces(int piecesLeft, int rowNo);
draw_box(int Xstart, int Xend, int Ystart, int Yend, int color);
void video_text(int x, int y, char * text_ptr);
clear_screen();
clear_char();
void plot_pixel(int x, int y, short int line_color);


int main() {
  //Initial setup
  int rowNo;
  int noPieces;
  int row[BOARD_SIZE][BOARD_SIZE];
  bool turn;
  bool gameOver;
  bool continueGame;
  int playerOneScore = 0, playerTwoScore = 0; //initial scores

  volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
  pixel_buffer_start = *pixel_ctrl_ptr;
  resetMatch( & turn, & gameOver, & continueGame, piecesRemaining, row);

  while (continueGame && !gameOver) {
    print(row);
	printGameGrid();
    bool invalidMove = true;
    while (invalidMove) {
      printf("Player %d: Which row would you like to remove pieces from? \n ", ((turn) ? 1 : 2));
      rowNo = receivedInput();
      //scanf( "%d", &rowNo);

      printf(" Player %d: How many pieces would you like to remove from %d? \n ", ((turn) ? 1 : 2), rowNo);
      noPieces = receivedInput();
      //scanf( "%d", &noPieces);

      invalidMove = removePieces(rowNo, noPieces, row);

    }

    if (checkWin(row)) { //Win occurred
      print(row);
		printGameGrid();
      printf("Player %d Wins the match!\n", ((turn) ? 1 : 2));
      gameOver = true;
      updateRounds(turn, & playerOneScore, & playerTwoScore);

      printf("Play Again? Press 'y' and hit ENTER");
      //scanf(" %c", & continueGame);
      continueGame = proceedGame();
      if (continueGame)
        resetMatch( & turn, & gameOver, & continueGame, piecesRemaining, row);
    }
    
    else { //No win occurred
    turn = turn ^ 1; //toggle turn        
    // printf("Continue? Press 'y' and hit ENTER");
    // continueGame = proceedGame();
    }

  }
  //game finished or user exited

  if (!continueGame)
    printf("User Exited Game");

  return 0;

}

int receivedInput() {
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
        *
        (PS2_ptr) = 0xF4;
      unsigned int shift_buffer[3];
      shift_buffer[2] = byte3;
      //printf("\nvalue is : %d", shift_buffer[2]);
      shift_buffer[1] = byte2;
      //printf("\nprev_value is : %d", shift_buffer[1]);
      shift_buffer[0] = byte1;
      //printf("\nprev2_value is : %d", shift_buffer[0]);

      if (shift_buffer[0] == 90 && shift_buffer[1] == 240 && shift_buffer[2] == 90) //Enter hit
        inputFinished = true;
      else if (shift_buffer[2] != 240 && shift_buffer[2] != 90)
        letterCode = shift_buffer[2];
    }
  }

  switch (letterCode) { //convert make code (in decimal) into key pressed
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

bool proceedGame() {
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
        *
        (PS2_ptr) = 0xF4;
      unsigned int shift_buffer[3];
      shift_buffer[2] = byte3;
      //printf("\nvalue is : %d", shift_buffer[2]);
      shift_buffer[1] = byte2;
      //printf("\nprev_value is : %d", shift_buffer[1]);
      shift_buffer[0] = byte1;
      //printf("\nprev2_value is : %d", shift_buffer[0]);

      if (byte1 == 90 && byte2 == 240 && byte3 == 90)
        inputFinished = true;
      else if (byte3 != 240 && byte3 != 90)
        letterCode = byte3;
    }
  }

  if (letterCode == 170) //if q is pressed
	  return false;
  return true;
}

void resetMatch(bool * turn, bool * gameOver, bool * continueGame, int * piecesRemaining, int row[BOARD_SIZE][BOARD_SIZE]) {

  * turn = true;
  * gameOver = false;
  * continueGame = true;

	clear_screen();
	clear_char();
	video_text(22,5,"NIM - STAY TILL THE LAST AND COME FIRST");
	
  //Randomize the distibution of the 21 pieces across the piles
  int totalCount = 21;
  //initliaze the # of game pieces in each row
  int randomNumber;
  for (int i = 0; i < BOARD_SIZE && totalCount > 0; i++) {
    randomNumber = rand() % 6 + 1; //random number from 1 to 6
    piecesRemaining[i] = randomNumber;
    totalCount -= randomNumber;
  }

  //for each board's row, set the correct number of pieces 
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < piecesRemaining[i]; j++) {
      row[i][j] = 1;
    }
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = piecesRemaining[i]; j < BOARD_SIZE; j++) {
      row[i][j] = 0;
    }
  }

}

bool removePieces(int rowNo, int noPieces, int row[BOARD_SIZE][BOARD_SIZE]) {
  rowNo--;
  if (rowNo < 0 || rowNo >= BOARD_SIZE) {
    printf("Invalid row #");
    return true;
  }
  int piecesLeftInRow = piecesRemaining[rowNo];
  if (noPieces > piecesLeftInRow || noPieces < 1) {
    printf("Invalid # of pieces");
    return true;
  }
  for (int k = piecesLeftInRow; k >= piecesLeftInRow - noPieces; k--) //update board display
  {
    row[rowNo][k] = 0;
  }
  piecesRemaining[rowNo] -= noPieces; //update the record of # of pieces left in board
  return false;
}

bool checkWin() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (piecesRemaining[i] != 0) // if a single piece is left
      return false;
  }
  return true; //empty board (no pieces left)
}

//no longer in use
void print(int row[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("Row %d\t", (i + 1));
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf("%d ", row[i][j]);

    }

    printf("\n");
  }
}

void printGameGrid(){
	clear_screen();
	for (int i = 0; i < BOARD_SIZE; i++){
		printPieces(piecesRemaining[i]+2, i);
	}
	
}

void updateRounds(bool turn, int * playerOneScore, int * playerTwoScore) {
  bool resetRounds = false;
  if (turn) {
    ( * playerOneScore) ++;
    if (( * playerOneScore) >= 5) {
      printf("Player One Wins the Round");
      resetRounds = true;
    }
  } else {
    ( * playerTwoScore) ++;
    if (( * playerTwoScore) >= 5) {
      printf("Player Two Wins the Round");
      resetRounds = true;
    }
  }
  if (resetRounds) {
    ( * playerOneScore) = 0;
    ( * playerTwoScore) = 0;
  }
}

void printPieces(int piecesLeft, int rowNo)
{
	bool black = false;
	for(int i=89;i<piecesLeft*2*20;i+=20)
	{
		if (!black){
			draw_box(i,i+20,((rowNo+1)*30+9), ((rowNo+1)*30)+29,0x07E0);
			//draw_box(i,i+20,30+ 9, 30+ 9 +20,0x07E0);
			 black = true;
		}
		else{
			 //draw_box(89,i+20,(rowNo*30)+ 9, (rowNo*30)+29,0xF800);
			  black = false;
	    }
		
	}

}

draw_box(int Xstart, int Xend, int Ystart, int Yend, int color)
{
	//clear_screen();
	for(int i= Xstart;i< Xend;i++)
	{
		for(int j= Ystart; j< Yend;j++)
		{
			plot_pixel(i,j,color);
		}
	}
}		

void video_text(int x, int y, char * text_ptr) {
	int offset;
	volatile char * character_buffer = (char*)0xC9000000;
	offset = (y << 7) + x; 
	while (*(text_ptr)) {
		*(character_buffer + offset) = *(text_ptr); // write to the character buffer
		++text_ptr;
		++offset;
	}
}
			  
clear_screen()
{
	for(int x=0; x<=319;x++)
	{
		for(int y=0;y<=239;y++)
		plot_pixel(x,y,0x0000);
	}
}
	
clear_char()
{
	for(int x=0; x<=79;x++)
	{
		for(int y=0;y<=59;y++)
		video_text(x,y," ");
	}
}


void plot_pixel(int x, int y, short int line_color)
{
     *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

		
	