//#include <cstdlib>
volatile int pixel_buffer_start; // global variable

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
void updateRounds(bool turn, int * playerOneScore, int * playerTwoScore);
void printPieces(int piecesRemaining, int rowNo);
draw_box(int Xstart, int Xend, int Ystart, int Yend, int color);
				 
				 
int main() {
    //Initial setup
    int rowNo;
    int noPieces;
    int row[BOARD_SIZE][BOARD_SIZE];
    bool turn;
    bool gameOver;
    char continueGame;
    int playerOneScore = 0, playerTwoScore = 0; //initial scores
	
	
	
	
	volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    pixel_buffer_start = *pixel_ctrl_ptr;
	clear_screen();
	clear_char();
	video_text(22,5,"NIM - STAY TILL THE LAST AND COME FIRST");
	//printPieces(2,3);
	//draw_box(189,209,99,119,0x0F1F);

    resetMatch (&turn, &gameOver, &continueGame, piecesRemaining, row);
   
    while(continueGame == 'y' && !gameOver)
    {
        print(row);
        bool invalidMove = true;
        while(invalidMove){
            printf( "Player %d: Which row would you like to remove pieces from? \n ", ((turn) ? 1 : 2));
            scanf( "%d", &rowNo);
                
            printf( " Player %d: How many pieces would you like to remove from %d? \n ",((turn) ? 1 : 2), rowNo);
            scanf( "%d", &noPieces);
            
            invalidMove = removePieces(rowNo, noPieces ,row);

        }

        if (checkWin(row)){
            print(row);

            printf("Player %d Wins the match!\n", ((turn) ? 1 : 2));
            gameOver = true;
            updateRounds(turn, &playerOneScore, &playerTwoScore);
            
            printf("Play Again? Press 'y' and hit ENTER");
            scanf(" %c", &continueGame);   
            if (continueGame == 'y')
                resetMatch (&turn, &gameOver, &continueGame, piecesRemaining, row);
        }
        else{
            turn = turn^1; //toggle turn        
            printf("Continue? Press 'y' and hit ENTER");
            scanf(" %c", &continueGame);  
        }
                
    }
	
	
    //game finished or user exited
    
    if (continueGame != 'y')
        printf("User Exited Game");
    
    return 0;
        
} 

void resetMatch(bool * turn, bool * gameOver, char * continueGame, int * piecesRemaining, int row[BOARD_SIZE][BOARD_SIZE]){
    
    *turn = true;
    *gameOver = false;
    *continueGame = 'y';
    
    //Randomize the distibution of the 21 pieces across the piles
    int totalCount = 21;
    //initliaze the # of game pieces in each row
    /*int randomNumber;
    for (int i = 0; i < BOARD_SIZE && totalCount > 0; i++){
        randomNumber = rand()%7; //random number from 0 to 6
        piecesRemaining[i] = randomNumber; 
        totalCount-=randomNumber;
		printPieces(piecesRemaining[i],i);
    }*/
	for (int i=0; i<6; i++){
        
        piecesRemaining[i] = i+3; 
        
		printPieces(piecesRemaining[i],i);
		//printPieces(6,4);
	
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
        
        
bool removePieces(int rowNo, int noPieces, int row[BOARD_SIZE][BOARD_SIZE])
{
    rowNo--;
    if (rowNo<0 || rowNo >= BOARD_SIZE){
        printf("Invalid row #");
        return true;
    }
    int piecesLeftInRow = piecesRemaining[rowNo];
    if (noPieces > piecesLeftInRow || noPieces < 1){
        printf("Invalid # of pieces");
        return true;
    }
    for (int k = piecesLeftInRow; k >= piecesLeftInRow - noPieces; k--) //update board display
    {
        row[rowNo][k] = 0;
    }
    piecesRemaining[rowNo]-=noPieces; //update the record of # of pieces left in board
    return false;
}

bool checkWin()
{
    for (int i =0; i< BOARD_SIZE;i++)
    {
        if (piecesRemaining[i] != 0) // if a single piece is left
            return false;
    }
    return true; //empty board (no pieces left)
}

void print(int row[BOARD_SIZE][BOARD_SIZE])
{
    for (int i =0; i< BOARD_SIZE;i++)
    {   
        printf("Row %d\t", (i+1));
        for(int j = 0;j < BOARD_SIZE; j++)
        {
            printf("%d ",row[i][j]);
                    
        }
        
        printf("\n");
    }
}        
      
void updateRounds(bool turn, int * playerOneScore, int * playerTwoScore){
    bool resetRounds = false;
    if (turn) {
        (*playerOneScore)++;
        if ((*playerOneScore)>=5){
            printf("Player One Wins the Round");
            resetRounds = true;
        }
    }
    else  {
        (*playerTwoScore)++;
        if ((*playerTwoScore)>=5){
            printf("Player Two Wins the Round");
            resetRounds = true;
        }
    }
    if (resetRounds){
        (*playerOneScore) = 0;
        (*playerTwoScore) = 0;
    }
}


void printPieces(int piecesRemaining, int rowNo)
{
	bool black = false;
	for(int i=89;i<piecesRemaining*2*20;i+=20)
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

		
		
		
	
	
	