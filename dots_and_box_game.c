#include<stdio.h>
char board[5][10]={"  1 2 3 4\n",
	     		   "a . . . .\n",
				   "b . . . .\n",
				   "c . . . .\n",
				   "d . . . .\n"};

int m_w,m_z;
int myScore=0,yourScore=0;
void printBoard(){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<10;j++){
			printf("%c",board[i][j]);
		}
	}
}
unsigned int get_random()
{
	m_z = 36969 * (m_z & 65535) + (m_z >> 16);
	m_w = 18000 * (m_w & 65535) + (m_w >> 16);
	return (m_z << 16) + m_w; /* 32-bit result */
}

unsigned isValid(int row1,int column1,int row2,int column2 ){
    if(row1<1 || row1>4) return 0;
    if(column1<1 || column1>4) return 0;
    if(row2<1 || row2>4) return 0;
    if(column2<1 || column2>4) return 0;
    return 1;

}

void play(){

int iteration=1,randomValue=1;
	randomValue=get_random()%10+1;
	iteration=iteration+randomValue;
	int prev=0;
	int isFirstMove=1;

    // will repeat 24 times with valid input
	while(iteration<=24+randomValue){
		char str1[3],str2[3];
		unsigned int row1,row2,column1,column2;
		if(iteration%2==0){
			if(iteration!=prev && !isFirstMove){
				printf("\nYour turn:\n");
				prev=iteration;
			}
			if(isFirstMove){
				printf("\nYou will make the first move.\n\n");
				isFirstMove=0;
			}
			printf("  Enter coordinate of the first dot: ");
			scanf("%s",str1);
			row1=str1[0]-'a'+1;
			column1=str1[1]-'0';
			printf("  Enter coordinate of the second dot: ");
			scanf("%s",str2);
			row2=str2[0]-'a'+1;
			column2=str2[1]-'0';
			if (!isValid(row1,column1,row2,column2)){printf("Invalid input, please try again\n"); continue ;}

		}else{
			if(isFirstMove){
				printf("\nI will make the first move.\n\n");
				isFirstMove=0;
			}

			row1=get_random()%4+1;
			row2=get_random()%4+1;
			column1=get_random()%4+1;
			column2=get_random()%4+1;
		}

		if(row1==row2){
			if(column1==column2+1||column1==column2-1){
				int min=column1<column2?column1:column2;
				if(board[row1][min*2+1]==' '){
					board[row1][min*2+1]='_';
					//check lower box
					if(row1!=4){
						if(board[row1+1][min*2]=='|'&& board[row1+1][min*2+2]=='|' && board[row1+1][min*2+1]=='_'){
							if(iteration%2==0){
								board[row1+1][min*2+1]='H';
								yourScore++;
							}
							else {
								board[row1+1][min*2+1]='C';
								myScore++;
							}
						}
					}
					//check upper box
					if(row1!=1){
						if(board[row1][min*2]=='|'&& board[row1][min*2+2]=='|' && board[row1-1][min*2+1]!=' '){
							if(iteration%2==0){
								board[row1][min*2+1]='H';
								yourScore++;
							}
							else{
								board[row1][min*2+1]='C';
								myScore++;
							}
						}
					}

					if(iteration%2!=0){
						printf("My turn: I draw between %c%d and %c%d\n\n",row1-1+'a',column1,row2-1+'a',column2);
						printBoard();
					}
					iteration++;
				}
				else {
					if(iteration%2==0)printf("There is already a line there.\n");
				}
			}
			else{
				if(iteration%2==0)printf("Coordinates must be adjacent\n");
			}
		}
		else{
			if((row1==row2+1||row1==row2-1)&&column1==column2){
				int max=(row1>row2?row1:row2);
				if(board[max][column1*2]!='|'){
					board[max][column1*2]='|';
					//check right box
					if(column1!=4){
						if(board[max][column1*2+1]=='_'&&board[max-1][column1*2+1]!=' '&&board[max][column1*2+2]=='|'){
							if(iteration%2==0){
								board[max][column1*2+1]='H';
								yourScore++;
							}
							else {
								board[max][column1*2+1]='C';
								myScore++;
							}
						}
					}
					//check left box
					if(column1!=1){
						if(board[max][column1*2-1]=='_' && board[max-1][column1*2-1]!=' '&&board[max][column1*2-2]=='|'){
							if(iteration%2==0){
								board[max][column1*2-1]='H';
								yourScore++;
							}
							else{
								board[max][column1*2-1]='C';
								myScore++;
							}
						}
					}

					if(iteration%2!=0){
						printf("My turn: I draw between %c%d and %c%d\n\n",row1-1+'a',column1,row2-1+'a',column2);
						printBoard();
					}
					iteration++;
				}
				else{
					if(iteration%2==0)printf("There is already a line there.\n");
				}
			}
			else{
				if(iteration%2==0)printf("Coordinates must be adjacent\n");
			}
		}
	}

}

int main(){

    printf("Welcome to Dots and Boxes!\nVersion 1.0\nImplemented by: \n1.Uddip Acharjee\n2.Obaidur Rahman\n3.Hasnuzzaman Hasan\n4.Tulshi Chandra Das\n\n");
	printBoard();
	printf("\nEnter two positive numbers to initialize the random number generator.\n");
	printf("Number 1: ");
	scanf("%d",&m_w);
	printf("Number 2: ");
	scanf("%d",&m_z);

    play();

	if(yourScore>myScore)printf("\nYou win!!\n\n");
	else printf("\nI win!!\n\n");
	printBoard();

}
