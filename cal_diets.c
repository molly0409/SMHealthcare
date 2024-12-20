//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;
//use for exit

/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
	
	FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
     //use fscanf. when read the string (%s) and the integer (%d) the loop is executed.
    while (fscanf(file,"%s %d", &diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake)==2) {
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
		
		diet_list_size++;
    }
    fclose(file);
    
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    //diet choice
	int di_choice,i;
    
	// ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    
	for (i=0;i<diet_list_size;i++)
	{
		printf("%i. %s\n",i+1,diet_list[i].food_name);
	}
	printf("%d. Exit\n",diet_list_size+1);
    
	// ToCode: to enter the diet to be chosen with exit option
    do{
		
		printf("choose the number:");
		scanf("%d",&di_choice);
		//choice is one of foods
		if(di_choice<=diet_list_size&&di_choice>0)
		{
			// ToCode: to enter the selected diet in the health data
			//health_data diet update
			strcpy(health_data->diet[health_data->diet_count].food_name,diet_list[di_choice-1].food_name);
			
    		//storage calorie intake
    		health_data->diet[health_data->diet_count].calories_intake=diet_list[di_choice-1].calories_intake;
    		
			//update total calories intake
			health_data->total_calories_intake+=health_data->diet[health_data->diet_count].calories_intake;
			health_data->diet_count++;
			break;
		}
		//choice is "exit"
    	else if(di_choice==diet_list_size+1)
    	{
    		printf("diet exit.go to main\n");
    		break;
		}
		//wrong choice number
		else
		{
			printf("[Error] Invalid option. \n");
            printf("Please try again! \n");
		}
	}while(1);
    

    // ToCode: to enter the total calories intake in the health data
	saveData("health_data.txt",health_data);

}

