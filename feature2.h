/* 
 * File:   feature2.h
 * Author: maxxeh
 *
 * Created on 11 December 2014, 06:09
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "navigation.h"
#include "structure_vars.h"
#include "feature1.h"


#ifndef FEATURE2_H
#define	FEATURE2_H

#ifdef	__cplusplus
extern "C" {
#endif

double avg(double one, double two)
{
    double average = (one + two) / 2;
    return average;
}
    
void set_true_location(sighting **sight_list)
{
    sighting *sight_current = *sight_list;
    sighting *sight2_current = *sight_list;
    double average_long;
    double average_lat;
    location accumulator;
    int count;
    
    while(sight_current != NULL)
    {
        count = 0;
        accumulator.lat = accumulator.lng = 0;
        while(sight2_current != NULL)
        {
            location location_current;
            location location2_current;
            location_current.lat = sight_current->loc.latitude;
            location_current.lng = sight_current->loc.longitude;
            location2_current.lat = sight2_current->loc.latitude;
            location2_current.lng = sight2_current->loc.longitude;
            if(great_circle(location_current, location2_current) < 0.02)
            {
                accumulator.lat += sight2_current->loc.latitude;
                accumulator.lng += sight2_current->loc.longitude;
                count ++;
            }
            sight2_current = sight2_current->next;
        }
        sight_current->actual_loc.latitude = accumulator.lat / count;
        sight_current->actual_loc.longitude = accumulator.lng / count;
        sight_current = sight_current->next;
        sight2_current = *sight_list;
    }
}

void print_locations_mission2(sighting **sight_list)
{
    sighting *sight_current = *sight_list;
    char m_type[11];
    printf("LATITUDE     LONGITUDE     ACTUAL LAT     ACTUAL LONG     MAMMAL TYPE     SIGHTED BY\n");
    printf("====================================================================================\n");
    while(sight_current != NULL)
    {
        if(52.00 <= sight_current->loc.latitude && sight_current->loc.latitude <= 52.833 && -4.000 >= sight_current->loc.longitude && sight_current->loc.longitude >= -5.500)
        {
            if(sight_current->mammal_type == 'D')
            {
                strcpy(m_type, "Dolphin");
            }
            else
            {
                strcpy(m_type, "Porpoise");
            }
            printf("%-11lf %-14lf %-13lf %-16lf %-15s %s\n", 
                    sight_current->loc.latitude, sight_current->loc.longitude, 
                    sight_current->actual_loc.latitude, 
                    sight_current->actual_loc.longitude, m_type, 
                    sight_current->obsid);
        }
        sight_current = sight_current->next;
    }
    printf("\n");
}


#ifdef	__cplusplus
}
#endif

#endif	/* FEATURE2_H */

