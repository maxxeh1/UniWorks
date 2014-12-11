/* 
 * File:   main.c
 * Author: maxxeh
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
    
    //File Input. Example file: observers_3.txt  sightings_3.txt
    printf("Please enter the name of the observer file: ");
    //scanf("%s", fileName);
    FILE* f1 = fopen("observers_5.txt", "r");
    //Error print if file problem
    if(f1 == NULL)
    {
        perror("Error opening file");
        return;
    }
    fscanf(f1, "%d %d %d %d %d %d", &dateTime.date, &dateTime.month, 
            &dateTime.year, &dateTime.hour, &dateTime.minute, &dateTime.second);
    while(fscanf(f1, "%4s %lf %lf", temp_id, &temp_lat, &temp_long) == 3)
    {
        struct observer *new_obs = make_observer(temp_id, temp_lat, temp_long);
        insert_observer(new_obs, &observer_start);
    }
    fclose(f1);
   
    printf("\nPlease enter the name of the mammal sighting file: ");
    //scanf("%s", fileName);
    FILE* f2 = fopen("sightings_5.txt", "r");
    while(fscanf(f2, "%4s %c %lf %lf", temp_obsid, &temp_mammal_type, 
            &temp_bearing, &temp_range) == 4)
    {
        struct sighting *new_sighting = make_sighting(temp_obsid, 
                temp_mammal_type, temp_bearing, temp_range);
        insert_sighting(new_sighting, &sighting_start);
        sighting_count++;
    }
    fclose(f2);
    printf("%d/%d/%d %d:%d:%d\n", dateTime.date, dateTime.month, 
            dateTime.year, dateTime.hour, dateTime.minute, dateTime.second);
    print_observer(&observer_start);
    print_sighting(&sighting_start);
    
    apply_mammal_locations(&observer_start, &sighting_start);
    print_locations(&sighting_start);
    
    set_true_location(&sighting_start);
    print_locations_mission2(&sighting_start);
    
    check_pod(&sighting_start);
    check_duplicates(&pod_start);
    print_pods(&pod_start);
}






