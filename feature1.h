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

    
    
observer* make_observer(char *id, double lat, double longitude)
{
    observer *node = (observer*) calloc(1, sizeof(observer));
    strcpy(node->id, id);
    node->lat = lat;
    node->longitude = longitude;
    node->next = NULL;
    return node;
}

sighting* make_sighting(char *obsid, char mammal_type, double bearing, 
        double range)
{
    sighting *node = (sighting*) calloc(1, sizeof(sighting));
    strcpy(node->obsid, obsid);
    node->mammal_type = mammal_type;
    node->bearing = bearing;
    node->range = range;
    node->loc.latitude = 0;
    node->loc.longitude = 0;
    node->actual_loc.latitude = 0;
    node->actual_loc.longitude = 0;
    node->duplicate_flag = 0;
    node->next = NULL;
    return node;
}

void insert_observer(observer *obs_node, observer **obs_list)
{
    if (*obs_list)
    {
        observer *obs_current = *obs_list;
        observer *obs_previous;
        while (obs_current)
        {
            obs_previous = obs_current;
            obs_current = obs_current->next;
        }
        obs_previous->next = obs_node;
    }
    else
        *obs_list = obs_node;
}

void insert_sighting(sighting *sight_node, sighting **sight_list)
{
    if (*sight_list)
    {
        sighting *sight_current = *sight_list;
        sighting *sight_previous;
        while (sight_current)
        {
            sight_previous = sight_current;
            sight_current = sight_current->next;
        }
        sight_previous->next = sight_node;
    }
    else
        *sight_list = sight_node;
}

void print_observer(observer **obs_list)
{
    if(obs_list == NULL)
    {
        printf("List is empty.\n\n");
        return;
    }
    observer *obs_current = *obs_list;
    while(obs_current != NULL)
    {
        printf("ID = %s Lat = %lf Long = %lf \n", obs_current->id, 
                obs_current->lat, obs_current->longitude);
        obs_current = obs_current->next;
    }
    printf("\n");
}
    
void print_sighting(sighting **sight_list)
{
    if(sight_list == NULL)
    {
        printf("List is empty.\n\n");
        return;
    }
    sighting *sight_current = *sight_list;
    while(sight_current != NULL)
    {
        printf("ID = %s Type = %c Bearing = %lf Range = %lf \n", 
                sight_current->obsid, sight_current->mammal_type, 
                sight_current->bearing, sight_current->range);
        sight_current = sight_current->next;
    }
    printf("\n");
}

struct mammal_location calculate_mammal_position(double obs_lat, double obs_longitude, 
        double bearing, double range)
{
    double bearing_radians = (bearing) * M_PI / 180.0;
    double o_lat_radians = (obs_lat) * M_PI / 180.0;
    double mammal_lat = obs_lat + (range * cos(bearing_radians)) / 60.0;
    double mammal_longitude = obs_longitude + (range * sin(bearing_radians))
    / cos(o_lat_radians) / 60.0;
    struct mammal_location new_loc;
    new_loc.latitude = mammal_lat;
    new_loc.longitude = mammal_longitude;
    return new_loc;
}

void apply_mammal_locations(observer **obs_list, sighting **sight_list)
{
    sighting *sight_current = *sight_list;
    observer *obs_current = *obs_list;
    
    while(sight_current != NULL)
    {
        while(obs_current != NULL)
        {
            if(!strcmp(sight_current->obsid, obs_current->id))
            {
                sight_current->loc = calculate_mammal_position(obs_current->lat, 
                        obs_current->longitude, sight_current->bearing, 
                        sight_current->range);
            }
            obs_current = obs_current->next;
        }
        sight_current = sight_current->next;
        obs_current = *obs_list;
    }
}

void print_locations(sighting **sight_list)
{
    sighting *sight_current = *sight_list;
    char m_type[11];
    printf("LATITUDE     LONGITUDE     MAMMAL TYPE     SIGHTED BY\n");
    printf("=====================================================\n");
    while(sight_current != NULL)
    {
        if(52.00 <= sight_current->loc.latitude && sight_current->loc.latitude <= 52.833 && -4.000 >= sight_current->loc.longitude && sight_current->loc.longitude >= -5.500)
            {
            if(sight_current->mammal_type == 'D')
            {
                strcpy(m_type, "Porpoise");
            }
            else
            {
                strcpy(m_type, "Dolphin");
            }
            printf("%-11lf %-14lf %-15s %s\n", sight_current->loc.latitude, 
                    sight_current->loc.longitude, m_type, sight_current->obsid);
            
        }
        sight_current = sight_current->next;
    }
    printf("\n");
}


#ifdef	__cplusplus
}
#endif

#endif	/* FEATURE1_H */

