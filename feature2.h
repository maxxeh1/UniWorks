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
    
    //Sets the averaged location of two sightings that refer to same mammal
    //Takes parameters: head of sighting list
    void set_true_location(sighting **sight_list)
    {
        //Creates two separate instances of the sight list and assigns them to 
        //head of sight list
        sighting *sight_current = *sight_list;
        sighting *sight2_current = *sight_list;
        //Creates instance of location to accumulate all lats and longs for avg
        location accumulator;
        int count;
        
        //Loop through first instance of sight list
        while(sight_current != NULL)
        {
            //Set required variables to nothing
            count = 0;
            accumulator.lat = accumulator.lng = 0;
            
            //Loop through second instance of sight list
            while(sight2_current != NULL)
            {
                //Set variables in location structure for use in great_circle 
                //function
                location location_current;
                location location2_current;
                location_current.lat = sight_current->loc.latitude;
                location_current.lng = sight_current->loc.longitude;
                location2_current.lat = sight2_current->loc.latitude;
                location2_current.lng = sight2_current->loc.longitude;
                
                //Uses great_circle function to check true distances
                if(great_circle(location_current, location2_current) < 0.02)
                {
                    //Accumulates lats and longs of all matched sightings from
                    //sight2 list only
                    accumulator.lat += sight2_current->loc.latitude;
                    accumulator.lng += sight2_current->loc.longitude;
                    //Keeps a count of how many sightings are matched
                    count ++;
                }
                //Moves to next element in second instance of list
                sight2_current = sight2_current->next;
            }
            
            //After second instance of list finishes iteration, take accumulated
            //lats and longs and divide by count to get averaged lat and long
            //Apply the averaged values to other location structure in sightings
            sight_current->actual_loc.latitude = accumulator.lat / count;
            sight_current->actual_loc.longitude = accumulator.lng / count;
            
            //Move to next element in first instance of list; reset second 
            //instance of list
            sight_current = sight_current->next;
            sight2_current = *sight_list;
        }
    }

    //Print all sightings with averaged locations 
    //Takes parameters: head of sighting list
    void print_locations_mission2(sighting **sight_list)
    {
        //Assign sight_current to head of sighting list
        sighting *sight_current = *sight_list;
        char m_type[11];
        
        printf("LATITUDE     LONGITUDE     ACTUAL LAT     ACTUAL LONG     "
                "MAMMAL TYPE     SIGHTED BY\n");
        printf("==============================================================="
                "=====================\n");
        
        //Loop through sighting list
        while(sight_current != NULL)
        {
            //Print only data within the designated sea area
            if(52.00 <= sight_current->loc.latitude && sight_current->
                    loc.latitude <= 52.833 && -4.000 >= sight_current->
                    loc.longitude && sight_current->loc.longitude >= -5.500)
            {
                //Print out full names of mammal type
                if(sight_current->mammal_type == 'D')
                {
                    strcpy(m_type, "Dolphin");
                }
                else
                {
                    strcpy(m_type, "Porpoise");
                }
                
                //Print each sighting data
                printf("%-11lf %-14lf %-13lf %-16lf %-15s %s\n", 
                        sight_current->loc.latitude, sight_current->loc.longitude, 
                        sight_current->actual_loc.latitude, 
                        sight_current->actual_loc.longitude, m_type, 
                        sight_current->obsid);
            }
            //Move to next element in list
            sight_current = sight_current->next;
        }
        printf("\n");
    }


#ifdef	__cplusplus
}
#endif

#endif	/* FEATURE2_H */

