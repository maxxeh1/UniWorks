/* 
 * File:   main.c
 * Author: Max Atkins
 *
 * Created on 04 December 2014, 20:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "navigation.h"
#include "structure_vars.h"
#include "feature1.h"
#include "feature2.h"
#include "feature3.h"

/*
 * 
 */

int main(int argc, char** argv) 
{
    //Main Local Variable Declarations
    char temp_id[11];
    double temp_lat;
    double temp_long;
    struct observer *observer_start = NULL;
    char temp_obsid[11];
    char temp_mammal_type;
    double temp_bearing;
    double temp_range;
    struct sighting *sighting_start = NULL;
    char fileName[51];
    int flag = 0;
    char continueInput;
    
    //Loop through everything if input is false
    do
    {
        //Allows user to choose to continue or quit
        printf("Welcome to the Sea Mammal Sightings Analyzer!\n");
        printf("Type 'Y' to continue or 'N' to exit: \n");
        scanf(" %c", &continueInput);
        if(continueInput == 'Y' || continueInput == 'y')
        {
            //File Input. Example file: observers_3.txt  sightings_3.txt
            printf("Please enter the name of the observer file: ");
            //Read in user input
            scanf("%s", fileName);
            FILE* f1 = fopen(fileName, "r");

            //Error print if file problem
            if(f1 == NULL)
            {
                perror("Error opening file");
                return;
            }
            //Read in first line; input into dateTime structure
            fscanf(f1, "%d %d %d %d %d %d", &dateTime.date, &dateTime.month, 
                    &dateTime.year, &dateTime.hour, &dateTime.minute, &dateTime
                    .second);
            //Read in every line that has three elements; input into observer 
            //structure and insert into observer linked list
            while(fscanf(f1, "%4s %lf %lf", temp_id, &temp_lat, &temp_long) 
                    == 3)
            {
                struct observer *new_obs = make_observer(temp_id, temp_lat, 
                        temp_long);
                insert_observer(new_obs, &observer_start);
            }
            fclose(f1);
            //File input. Examples above
            printf("\nPlease enter the name of the mammal sighting file: ");
            //Read in user input
            scanf("%s", fileName);
            FILE* f2 = fopen(fileName, "r");
            //Read in every line that has four elements; input into sightings 
            //structure and insert into sightings linked list
            while(fscanf(f2, "%4s %c %lf %lf", temp_obsid, &temp_mammal_type, 
                    &temp_bearing, &temp_range) == 4)
            {
                struct sighting *new_sighting = make_sighting(temp_obsid, 
                        temp_mammal_type, temp_bearing, temp_range);
                insert_sighting(new_sighting, &sighting_start);
                //Increment sighting_count to keep track of number of sightings
                sighting_count++;
            }
            fclose(f2);
            
            //Print time and date
            printf("%d/%d/%d %d:%d:%d\n", dateTime.date, dateTime.month, 
                    dateTime.year, dateTime.hour, dateTime.minute, 
                    dateTime.second);
            
            //Commented out debugging functions
            //print_observer(&observer_start);
            //print_sighting(&sighting_start);
            
            //Mission 1 - All functions (including Linked List) are in 
            //feature1.h
            apply_mammal_locations(&observer_start, &sighting_start);
            print_locations(&sighting_start);
            
            //Loop through Feature 2 stuff if input is false
            do
            {
                printf("Type 'Y' to continue or 'N' to exit: \n");
                scanf(" %c", &continueInput);
                if(continueInput == 'Y' || continueInput == 'y')
                {
                    //Mission 2 - All functions are in feature2.h
                    set_true_location(&sighting_start);
                    print_locations_mission2(&sighting_start);
                    
                    //Loop through Feature 3 stuff if input is false
                    do
                    {
                        printf("Type 'Y' to continue or 'N' to exit: \n");
                        scanf(" %c", &continueInput);
                        if(continueInput == 'Y' || continueInput == 'y')
                        {
                            //Mission 3 - All functions are in feature3.h
                            check_pod(&sighting_start);
                            check_duplicates(&pod_start);
                            print_pods(&pod_start);
                            
                            //Allow user to exit program
                            printf("Press any key and return to exit\n"); 
                            scanf(" ", &continueInput);
                            printf("Thank you for using the Sea Mammal "
                                    "Sightings Analyzer\n");
                            //Exit Program
                            return (EXIT_SUCCESS);
                        }
                        else if(continueInput == 'N' || continueInput == 'n')
                        {
                            //Exit Program
                            printf("Thank you for using the Sea Mammal "
                                    "Sightings Analyzer\n");
                            return (EXIT_SUCCESS);
                        }
                        else
                        {
                            //Loop back to start; clear continueInput for scanf
                            printf("Please enter a valid character\n");
                            continueInput = 0;
                        }
                    //Loop forever
                    }while(1);
                }
                else if(continueInput == 'N' || continueInput == 'n')
                {
                    //Exit Program
                    printf("Thank you for using the Sea Mammal Sightings "
                            "Analyzer\n");
                    return (EXIT_SUCCESS);
                }
                else
                {
                    //Loop back to start; clear continueInput for scanf
                    printf("Please enter a valid character\n");
                    continueInput = 0;
                }
            //Loop forever
            }while(1);
        }
        else if(continueInput == 'N' || continueInput == 'n')
        {
            //Exit Program
            printf("Thank you for using the Sea Mammal Sightings Analyzer\n");
            return (EXIT_SUCCESS);
        }
        else
        {
            //Loop back to start; clear continueInput for scanf
            printf("Please enter a valid character\n");
            continueInput = 0;
        }
    //Loop forever
    }while(flag == 0);
    
    //Exit incase above code doesn't for some reason
    return (EXIT_SUCCESS);
}






