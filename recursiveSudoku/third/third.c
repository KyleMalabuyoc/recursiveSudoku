#include<stdio.h>
#include<stdlib.h>

int sudokuFill(int** table);

int main(int argc, char** argv){

	if(argc < 2){
		printf("error\n");
		return 0;
	}
	FILE *fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("error\n");
		return 0;
	}
		int** table;
		table = (int**)malloc(9*sizeof(int*));
		int i,j;	

	for(i = 0; i < 9; i++){
		table[i] = (int*)malloc(9*sizeof(int));
	}
			for(i = 0; i < 9; i++){
			
				for(j = 0; j < 9; j++){
					if(!fscanf(fp, "%d ", &table[i][j])){ //assign dashes to 0
						table[i][j] = 0;	
				}
			}	
		}

	fclose(fp); //close file

	int negNum = 0;
	int x,y,error = 0;

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(table[i][j] < 0){
				negNum = 1;
			}
		}
	}

	if(negNum == 1){
		printf("no-solution");
		return 0;
	}
	
	for(i = 0; i < 9; i++){ //error check beginning of board
			y = 0;
		for(x = 0; x < 9; x++){
				y = y+1;
			for(j = y; j < 9; j++){

				if(table[i][x] == table[i][j] && table[i][x] != 0){
					error = 1;
				}
				if(table[x][i] == table[j][i] && table[x][i] != 0){
					error = 1;
				}
			}
		}
	}
	if(error == 1){
		printf("no-solution");
		return 0;
	}

	sudokuFill(table); //fill out the table

	for(i = 0; i < 9; i++){ //error check after board is filled
			y = 0;
		for(x = 0; x < 9; x++){
				y = y+1;
			for(j = y; j < 9; j++){
				if(table[i][x] == table[i][j]){
					error = 1;
				}
				if(table[x][i] == table[j][i]){
					error = 1;
				}
			}

		}

	}

	if(error == 1){
		printf("no-solution");
		return 0;
	}

	for(i = 0; i < 9;i++){

		for(j = 0; j < 9; j++){

			printf("%d\t",table[i][j]);

		}
		printf("\n");
	}

	return 0;
}
int sudokuFill(int** table){
	
	int i,j;
	int unassigned = 0;
	int num,check,col,row;
	int colP = 0, rowP = 0, boxP = 0;

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(table[i][j] == 0){
				unassigned = 1;
				break;
			}
		}

		if(unassigned == 1){
			break;
		}
	}

	if(unassigned == 0){
		return 1; //all spots are filled

	}else if(unassigned == 1){

	for(num = 1; num <= 9; num++){

		colP = 0;
		rowP = 0;
		boxP = 0;

		for(check = 0; check < 9; check++){ 

			if(table[i][check] == num){//row check
				rowP = 1;
			}

			if(table[check][j] == num){ //col check
				colP = 1; //match found
			}
		}

			//3x3 box check
			if(i < 3 && j < 3){ //check first subgrid top section
	
				for(row = 0; row < 3; row++){
				
					for(col = 0; col < 3; col++){
						if(table[row][col] == num){
							boxP = 1;
						
						}
					}
				}
			}

			else if(i > 2 && i < 6 && j < 3){ //check first subgrid middle section

				for(row = 3; row < 6; row++){
				
					for(col = 0; col < 3; col++){
						if(table[row][col] == num){
							boxP = 1;
							
						}
					}
				}

			}

			else if(i > 5 && j < 3){ //check first subgrid bottom section

				for(row = 6; row < 9; row++){
				
					for(col = 0; col < 3; col++){
						if(table[row][col] == num){
							boxP = 1;
							
						}
					}
				}
			}
	
			else if(i < 3 && j > 2 && j < 6){ //check mid subgrid top section

				for(row = 0; row < 3; row++){
					for(col = 3; col < 6; col++){
						if(table[row][col] == num){
							boxP = 1;
						
						}
					}
				}	

			}

			else if(i > 2 && i < 6 && j > 2 && j < 6){ //check mid subgrid middle section

				for(row = 3; row < 6; row++){
					for(col = 3; col < 6; col++){
						if(table[row][col] == num){
							boxP = 1;
							
						}
					}
				}	

			}

			else if(i > 5 && j > 2 && j < 6){ //check mid subgrid bottom section

				for(row = 6; row < 9; row++){
					for(col = 3; col < 6; col++){
						if(table[row][col] == num){
							boxP = 1;
					
						}
					}
				}	

			}

			else if(i < 3 && j > 5){ //checkk last subgrid top section
				
				for(row = 0; row < 3; row++){
					for(col = 6; col < 9; col++){
						if(table[row][col] == num){
							boxP = 1;
							
						}
					}
				}
			}

			else if(i > 2 && i < 6 && j > 5){ //check last subgrid middle section
				
				for(row = 3; row < 6; row++){
					for(col = 6; col < 9; col++){
						if(table[row][col] == num){
							boxP = 1;
						
						}
					}
				}
			}
	
			else if(i > 5 && j > 5){ //check last subgrid bottom section
				
				for(row = 6; row < 9; row++){
					for(col = 6; col < 9; col++){
						if(table[row][col] == num){
							boxP = 1;
							
						}
					}
				}

			}
		
		if(colP == 0 && rowP == 0 && boxP == 0){//number passed all tests

			table[i][j] = num;

			int val = sudokuFill(table);

			if(val == 0){
				table[i][j] = 0; //reset the value to zero, try new number

			}else if(val == 1){
				return 1; //done

			}
		}

	}
}
	return 0;	
}
