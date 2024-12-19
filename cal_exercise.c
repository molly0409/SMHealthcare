//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;
//declare the structure of exercise tatal data
int total_duration[MAX_EXERCISES]={0};
/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
	
	FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    //use fscanf. when read the string (%s) and the integer (%d) the loop is executed.
    while (fscanf(file,"%s %d", &exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute)==2) 
	{
    	
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
			
		exercise_list_size++;
    }
    fclose(file);      
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    int ex_choice;
    
	// ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
	
	for (i=0;i<exercise_list_size;i++)
	{
		printf("%i. %s\n",i+1,exercise_list[i].exercise_name);
	}
	printf("%d. Exit\n",exercise_list_size+1);
    
	// ToCode: to enter the exercise to be chosen with exit option
	do{
		
		printf("choose the number:");
		scanf("%d",&ex_choice);
		
		if(ex_choice<=exercise_list_size&&ex_choice>0)
		{
			//health_data exercise update
			strcpy(health_data->exercises[health_data->exercise_count].exercise_name,exercise_list[ex_choice - 1].exercise_name);
			
			// To enter the duration of the exercise
    		printf("Enter the duration of the exercise (in min.): ");
    		scanf("%d", &duration);
    		//storage calories per minute
    		health_data->exercises[health_data->exercise_count].calories_burned_per_minute=exercise_list[ex_choice - 1].calories_burned_per_minute;
    		//duration 
			total_duration[ex_choice-1]+=duration;
			
			printf("%s %d",health_data->exercises[health_data->exercise_count].exercise_name,health_data->exercises[health_data->exercise_count].calories_burned_per_minute);
			health_data->exercise_count++;
			break;
		}
    	else if(ex_choice==exercise_list_size+1)
    	{
    		printf("program exit.");
    		choice=4;
    		break;
		}
		else
		{
			printf("[Error] Invalid option. \n");
            printf("Please try again! \n");
		}
	}while(1);
    
	
    // ToCode: to enter the selected exercise and total calcories burned in the health data
    saveData("health_data.txt",health_data);
	
}
