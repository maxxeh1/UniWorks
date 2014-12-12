/* 
 * File:   feature1.h
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


#ifndef FEATURE1_H
#define	FEATURE1_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Makes an observer and sets parameters to variables in struct
    //Takes parameters: observer id, latitude, longitude from observer structure
    //Returns: An observer structure
    observer* make_observer(char *id, double lat, double longitude)
    {
        //Allocates memory for the observer struct
        observer *node = (observer*) calloc(1, sizeof(observer));
        strcpy(node->id, id);
        node->lat = lat;
        node->longitude = longitude;
        node->next = NULL;
        return node;
    }

    //Makes a sighting and sets parameters to variables in struct
    //Takes parameters: observer id, mammal type, bearing, range from sighting 
    //structure
    //Returns: A sighting structure
    sighting* make_sighting(char *obsid, char mammal_type, double bearing, 
            double range)
    {
        //Allocates memory for the sighting struct
        sighting *node = (sighting*) calloc(1, sizeof(sighting));
        strcpy(node->obsid, obsid);
        node->mammal_type = mammal_type;
        node->bearing = bearing;
        node->range = range;
        //All below set variables to nothing to ensure no unwanted data is in
        node->loc.latitude = 0;
        node->loc.longitude = 0;
        node->actual_loc.latitude = 0;
        node->actual_loc.longitude = 0;
        node->duplicate_flag = 0;
        node->next = NULL;
        return node;
    }

    //Insert an observer struct into the linked list
    //Takes parameters: Observer structure, head of observer list
    void insert_observer(observer *obs_node, observer **obs_list)
    {
        //If there is something in the list
        if (*obs_list)
        {
            //Set obs_current to the head of observer linked list
            observer *obs_current = *obs_list;
            observer *obs_previous;
            //Iterate through linked list to the end
            while (obs_current)
            {
                //Set obs_previous to current and move current to next item
                obs_previous = obs_current;
                obs_current = obs_current->next; 
            }
            //Assign the empty next to node
            obs_previous->next = obs_node;
        }
        else //If there's nothing in list, add something to head
        {
            *obs_list = obs_node;
        }
    }

    //Insert an sighting struct into the linked list
    //Takes parameters: Sighting structure, head of sighting list
    void insert_sighting(sighting *sight_node, sighting **sight_list)
    {
        //If there is something in the list
        if (*sight_list)
        {
            //Set sight_current to the head of sighting linked list
            sighting *sight_current = *sight_list;
            sighting *sight_previous;
            //Iterate through linked list to the end
            while (sight_current)
            {
                //Set sight_previous to current and move current to next item
                sight_previous = sight_current;
                sight_current = sight_current->next;
            }
            //Assign the empty next to node
            sight_previous->next = sight_node;
        }
        else //If there's nothing in list, add something to head
        {
            *sight_list = sight_node;
        }
    }

    //Print all observers for debugging
    //Takes parameters: head of observer list
    void print_observer(observer **obs_list)
    {
        //If list is empty
        if(obs_list == NULL)
        {
            printf("List is empty.\n\n");
            return;
        }
        //Set obs_current to head of observer linked list
        observer *obs_current = *obs_list;
        //Iterate through linked list
        while(obs_current != NULL)
        {
            //Print each element of linked list
            printf("ID = %s Lat = %lf Long = %lf \n", obs_current->id, 
                    obs_current->lat, obs_current->longitude);
            //Move to next element in linked list
            obs_current = obs_current->next;
        }
        printf("\n");
    }

    //Print all sightings for debugging
    //Takes parameters: head of sighting list
    void print_sighting(sighting **sight_list)
    {
        //If list is empty
        if(sight_list == NULL)
        {
            printf("List is empty.\n\n");
            return;
        }
        //Set sight_current to head of sighting linked list
        sighting *sight_current = *sight_list;
        while(sight_current != NULL)
        {
            //Print each element of linked list
            printf("ID = %s Type = %c Bearing = %lf Range = %lf \n", 
                    sight_current->obsid, sight_current->mammal_type, 
                    sight_current->bearing, sight_current->range);
            //Move to next element in linked list
            sight_current = sight_current->next;
        }
        printf("\n");
    }

    //Calculate position of the mammal based on observer data && sighting data
    //Takes parameters: (observer) lat, long (sighting) bearing and range
    //Returns: mammal_location structure
    struct mammal_location calculate_mammal_position(double obs_lat, 
            double obs_longitude, double bearing, double range)
    {
        //Convert degrees to radians
        double bearing_radians = (bearing) * M_PI / 180.0;
        double o_lat_radians = (obs_lat) * M_PI / 180.0;
        //Calculate latitude
        double mammal_lat = obs_lat + (range * cos(bearing_radians)) / 60.0;
        //Calculate longitude
        double mammal_longitude = obs_longitude + (range * sin(bearing_radians))
        / cos(o_lat_radians) / 60.0;
        //Create new structure to hold location data
        struct mammal_location new_loc;
        //Assign variables to new structure
        new_loc.latitude = mammal_lat;
        new_loc.longitude = mammal_longitude;
        return new_loc;
    }

    //Applies observer data to sighting data and calculates necessary data
    //Takes parameters: head of observer list && head of sighting list
    void apply_mammal_locations(observer **obs_list, sighting **sight_list)
    {
        //Set current element to each list head
        sighting *sight_current = *sight_list;
        observer *obs_current = *obs_list;
        
        //Loop through sighting list
        while(sight_current != NULL)
        {
            //Loop through observer list
            while(obs_current != NULL)
            {
                //Compare ids in each element, execute block if same
                if(!strcmp(sight_current->obsid, obs_current->id))
                {
                    //Apply calculate_mammal_position function to loc structure
                    //in sighting structure
                    sight_current->loc = 
                            calculate_mammal_position(obs_current->lat, 
                            obs_current->longitude, sight_current->bearing, 
                            sight_current->range);
                }
                //Move to next element in list
                obs_current = obs_current->next;
            }
            //Move to next element in list
            sight_current = sight_current->next;
            //Reset observer current to head of list
            obs_current = *obs_list;
        }
    }
    
    //Print all sightings in relevant sea area with calculated locations
    //Takes parameters: head of sighting list
    void print_locations(sighting **sight_list)
    {
        //Set sight_current to head of sighting list
        sighting *sight_current = *sight_list;
        char m_type[11];
        
        printf("LATITUDE     LONGITUDE     MAMMAL TYPE     SIGHTED BY\n");
        printf("=====================================================\n");
        
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
                printf("%-11lf %-14lf %-15s %s\n", sight_current->loc.latitude, 
                        sight_current->loc.longitude, m_type, sight_current->obsid);

            }
            //Move to next element in list
            sight_current = sight_current->next;
        }
        printf("\n");
    }


#ifdef	__cplusplus
}
#endif

#endif	/* FEATURE1_H */

