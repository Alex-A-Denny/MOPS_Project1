//
// File: ahnentafel.c
//
// @author Alex A Denny aad7700@g.rit.edu
// 
//////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"


Result tenToTwo(int num){

	Result res;//declaring struct

	if (num == 1) {//input validation for self
		res.integer = (int*)malloc(sizeof(int));
       		res.integer[0] = 1;
		res.index = 1;
		return res;
    	}

	//declaring vars
    	int* binary = (int*) malloc(sizeof(int) * 32); // Assuming 32-bit integers
    	int index = 0;

	//converting base 10 num to base 2
    	while (num != 0) {
		binary[index] = num % 2;
        	num /= 2;
		index++;
    	}

	//assing res values
	binary = (int*) realloc(binary, sizeof(int) * index);
	res.integer = binary;
	res.index = index;

	return res;
}

Result twoToTen(int num){

	Result res;//declaring struct

    	if (num == 1) {//input validation for self
        	res.integer = (int*)malloc(sizeof(int));
        	res.integer[0] = 1;
        	res.index = 1;
        	return res;
    	}

	//declaring vars
	int decimal = 0;
    	int base = 1;

	//converting base 2 to base 10
    	while (num != 0) {
        	int digit = num % 10;
        	decimal += digit * base;
        	num /= 10;
        	base *= 2;
    	}

	//assing res values
    	res.integer = (int*)malloc(sizeof(int));
    	res.integer[0] = decimal;
    	res.index = 1;

    	return res;
}

void relation(Result res){

	//checking for self
	if(res.index == 1){
		printf("self");
	}

	char* str = (char*)malloc(sizeof(char) * 100); // Adjust the size as needed
    	strcpy(str, ""); // Initialize the string

	for (int i = 1; i < res.index; i++){//skips self
	
		if(res.integer[i] == 1){//mother
		
			if(i != res.index - 1){//middle ancestor
				strcat(str, "mother's ");
			}
			else{//final ancestor
				strcat(str, "mother\n");
			}
		}
		else if(res.integer[i] == 0){//father

                        if(i != res.index - 1){//middle ancestor
                                strcat(str, "father's ");
                        }
                        else{//final ancestor
                                strcat(str, "father\n");
                        }
                }
	
	}

	//displaying output and freeing
	printf("%s", str);
	free( str );
}

int gens_back(Result res){
	//calculating generations back
	//res.index is always accounting
	//for a base 2 integer
	//when this iscalled
	return res.index - 1;
}

void num_cmdTwo(int num){
	
	//printing start
	printf("base-2 value: ");

	//creating Result struct
	Result res = tenToTwo(num);
		
	//displaying base 2 value
    	for (int i = 0; i < res.index; i++) {
        	printf("%d", res.integer[i]);
    	}
	
	//printing family relations and generations back
	printf("\nfamily relations: ");
	relation(res);
	printf("\ngenerations back: %d\n", gens_back(res));	
	
	free( res.integer );
}


void num_cmdThree(int num) {
	
	//declaring struct
	Result res;

        char tmp[20]= "";//temporary string to get the len of num
        sprintf(tmp, "%d", num);
        int elements = strlen(tmp);
	int * binary = (int*) malloc(sizeof(int) * elements);
	
	//keeping base two num for later
	for(int i = 0; i < elements; i++){
		binary[i] = tmp[i] - '0';
	}

	//printing start
	printf("base-10 value: ");
	

        res = twoToTen(num);//convert to base 10

	//displaying base 10 value
        for (int i = 0; i < res.index; i++) {
                printf("%d", res.integer[i]);
        }
	
	//replacing base 2 into integer
	//for use in relations()
	//and gens_back()
	free( res.integer );
	res.integer = binary;
	res.index = elements;
	

	//displaying relations and gens_back
        printf("\nfamily relations: ");
        relation(res);
	printf("generations back: %d\n", gens_back(res));

	free( binary );
}

void num_cmdFour(Result res, int num){

	//finding gens_back early
	int gens = gens_back(res);

	//printing start
	printf("ahnentafel number in binary: ");

	//printing num
	for(int i = 0; i < res.index; i++){
		printf("%d", res.integer[i]);
	}
	
	//converting to base 10
	res = twoToTen(num);

	//printing base 10 and gens_back
    	printf("\nahnentafel number in base-10: %d\n", *res.integer);
    	printf("generations back: %d\n", gens);

	free( res.integer );
}

//helper that converts and int* to normal int
int arrayToInt(int* arr, int size) {
    int result = 0;
    int multiplier = 1;

    // Start from the least significant digit and accumulate the value
    for (int i = size - 1; i >= 0; i--) {
        result += arr[i] * multiplier;
        multiplier *= 10;
    }

    return result;
}


int main(int argc, char *argv[]){

	//declaring var
	char * input = (char *) malloc(sizeof(char) * 243);
	input[0] = '\0';


	//diplaying commands
        printf("1) description\n"
		"2) ahnentafel number (base 10)\n"
		"3) ahnentafel number (base 2)\n"
                "4) relation (e.g. mother’s mother’s father)\n"
                "5) exit\n");

	//user input
	while(atoi(input) != 5){
		
		fgets(input, 243, stdin);

		//function calls / output
		if(atoi(input) == 1){//description command
		
			printf("The Ahnentafel number is used to determine the relation\n"
				"between an individual and each of his/her direct ancestors.\n");
		
		}
		else if(atoi(input) == 2){//base 10 input
			
			int num;
			printf("Enter the ahnentafel number in base-10: ");
			scanf("%d", &num);
			getchar();//consumes newline character

			num_cmdTwo(num);
		
		}
		else if(atoi(input) == 3){//base 2 input

                        int num;
                        printf("Enter the ahnentafel number in base-2: ");
                        scanf("%d", &num);
                        getchar();//consumes newline character

                        num_cmdThree(num);

                }
		else if(atoi(input) == 4){//string input

                        //getting relations input
                        printf("Enter family relation (e.g.) \"father’s mother\": ");
			char * relation = (char*) malloc(243);
			fgets(relation, 243, stdin);
			char * delim = "'s ";

			//tokenizing
			char * token = strtok(relation, delim);
			
			int elements = 1;
			int * binary = (int*) malloc(sizeof(int) * elements);
			binary[0] = 1;
			
			//creating base 2 num with given relation string
			char self = 's';
			if(strncmp(token, &self, 1) != 0){
			
				while(token != NULL){
                                	char father = 'f';
                                	char mother = 'm';

                                	if(strncmp(token, &mother, 1) == 0) {

                                        	binary = (int*) realloc(binary, sizeof(int) * (elements + 1));
                                        	binary[elements] = 1;
                                        	elements++;

                                	}
                                	else if (strncmp(token, &father, 1) == 0){

                                        	binary = (int*) realloc(binary, sizeof(int) * (elements + 1));
                                        	binary[elements] = 0;
                                        	elements++;

                                	}

                                	token = strtok(NULL, delim);

                        	}
			
			}
			
			//turing int array into int
			int num = arrayToInt(binary, elements);
			
			
			//creating Result struct and
			//finally entering the 4 command
			//function
			Result res;
			res.integer = binary;
			res.index = elements;
                        num_cmdFour(res, num);

			free( relation );
			free( binary );

                }

		if(atoi(input) != 5){//diplaying commands message
                	printf("1) description\n"
                        	"2) ahnentafel number (base 10)\n"
                        	"3) ahnentafel number (base 2)\n"
                        	"4) relation (e.g. mother’s mother’s father)\n"
                        	"5) exit\n\n\n");
		}
	}

	//goodbye message after user is done
	printf("Goodbye.\n");

	//freeing
        free( input );

	return EXIT_SUCCESS;

}
