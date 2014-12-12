/* 
 * File:   feature3.h
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
#include "feature2.h"

#ifndef FEATURE3_H
#define	FEATURE3_H

#ifdef	__cplusplus
extern "C" {
#endif  
    
    //Makes a pod structure with no values
    //Returns: created pod structure
    pod* make_pod()
    {
        //Create pod structure with size of the structure
        pod *node = (pod*) calloc(1, sizeof(struct pod));
        //Create array of sighting structures with size of number of sightings
        node->sightings = calloc(sighting_count, sizeof(struct sighting));
        node->next = NULL;
        node->sighting_index = 0;
        return node;
    }

    //Insert a pod structure into a pod linked list
    //Takes parameters: a pod structure, head of pod list
    void insert_pod(pod *pod_node, pod **pod_list)
    {
        if (*pod_list)
        {
            pod *pod_current = *pod_list;
            pod *pod_previous;
            while (pod_current)
            {
                pod_previous = pod_current;
                pod_current = pod_current->next;
            }
            pod_previous->next = pod_node;
        }
        else
            *pod_list = pod_node;
    }

    void remove_sighting(sighting *sight_node, sighting **sight_list)
    {
        sighting *sight_current = *sight_list;
        sighting *sight_previous;
        while(sight_current != NULL)
        {
            if(sight_node == *sight_list)
            {
                *sight_list = sight_node->next;
                free(sight_node);
                return;
            }
            else if(sight_node == sight_current)
            {
                sight_previous->next = sight_current->next;
                free(sight_current);
                return;
            }
            sight_previous = sight_current;
            sight_current = sight_current->next;
        }
    }

    void check_pod(sighting **sight_list)
    {
        sighting *sight_current = *sight_list;
        struct sighting *sight_start = NULL;
        struct sighting *temp_container = NULL;
        int flag = 0;

        while(sight_current != NULL)
        {
            char temp_obsid[11];
            strcpy(temp_obsid, sight_current->obsid);
            char temp_mammal;
            temp_mammal = sight_current->mammal_type;
            double temp_bearing = sight_current->bearing;
            double temp_range = sight_current->range;
            struct sighting *sight_copy = make_sighting(temp_obsid, temp_mammal, 
                    temp_bearing, temp_range);
            sight_copy->loc.latitude = sight_current->loc.latitude;
            sight_copy->loc.longitude = sight_current->loc.longitude;
            sight_copy->actual_loc.latitude = sight_current->actual_loc.latitude;
            sight_copy->actual_loc.longitude = sight_current->actual_loc.longitude;
            insert_sighting(sight_copy, &sight_start);
            sight_current = sight_current->next;
        }
        sight_current = *sight_list;
        sighting *sight2_current = sight_start;
        while(sight_current != NULL)
        {
            struct pod *new_pod = make_pod();
            while(sight2_current != NULL)
            {
                temp_container = sight2_current;
                location location_current;
                location location2_current;
                location_current.lat = sight_current->loc.latitude;
                location_current.lng = sight_current->loc.longitude;
                location2_current.lat = sight2_current->loc.latitude;
                location2_current.lng = sight2_current->loc.longitude;
                if(great_circle(location_current, location2_current) < 0.1)
                {
                    if(flag == 0)
                    {
                        insert_pod(new_pod, &pod_start);
                        flag = 1;
                    }
                    new_pod->sightings[new_pod->sighting_index++] = *sight2_current;
                    remove_sighting(sight2_current, &sight_start);
                }
                sight2_current = temp_container->next;
            }
            flag = 0;
            sight2_current = sight_start;
            sight_current = sight_current->next;
        }
    }

    void check_duplicates(pod **pod_list)
    {
        pod *pod_current = *pod_list;
        int i, j;
        while(pod_current != NULL)
        {
            for(i = 0; i < pod_current->sighting_index; i++)
            {
                for(j = 0; j < pod_current->sighting_index; j++)
                {
                    if(j != i)
                    {
                        if(pod_current->sightings[i].actual_loc.latitude == 
                                pod_current->sightings[j].actual_loc.latitude && 
                                pod_current->sightings[i].actual_loc.longitude == 
                                pod_current->sightings[j].actual_loc.longitude)
                        {
                            if(pod_current->sightings[i].duplicate_flag == 0)
                            {
                                pod_current->sightings[j].duplicate_flag = 1;
                            }
                        }
                    }
                }
            }
            pod_current = pod_current->next;
        }

    }

    void print_pods(pod **pod_list)
    {
        pod *pod_current = *pod_list;
        int i;
        int count = 0;
        int pod_count = 0;
        char m_type[11];


        printf("LATITUDE     LONGITUDE     MAMMAL TYPE     SIGHTED BY\n");
        printf("=====================================================\n");
        while(pod_current != NULL)
        {
            pod_count = 0;
            for(i = 0; i < pod_current->sighting_index; i++)
            {
                if(52.00 <= pod_current->sightings[i].loc.latitude && pod_current->
                sightings[i].loc.latitude <= 52.833 && -4.000 >= pod_current->
                sightings[i].loc.longitude && pod_current->sightings[i].loc.
                longitude >= -5.500)
                {
                    if(pod_current->sightings[i].duplicate_flag == 0)
                    {
                        pod_count++;
                    }
                }
            }
            if(pod_count > 1)
            {
                count++;
                printf("Pod %d\n", count);
                printf("-----------------------------------------------------\n");


                    for(i = 0; i < pod_current->sighting_index; i++)
                    {
                        if(52.00 <= pod_current->sightings[i].loc.latitude && pod_current->
                        sightings[i].loc.latitude <= 52.833 && -4.000 >= pod_current->
                        sightings[i].loc.longitude && pod_current->sightings[i].loc.
                        longitude >= -5.500)
                        {
                            if(pod_current->sightings[i].duplicate_flag == 0)
                            {
                                if(pod_current->sightings[i].mammal_type == 'D')
                                {
                                    strcpy(m_type, "Dolphin");
                                }
                                else
                                {
                                    strcpy(m_type, "Porpoise");
                                }

                                printf("%-11lf %-14lf %-15s %s\n",  
                                        pod_current->sightings[i].actual_loc.latitude, 
                                        pod_current->sightings[i].actual_loc.longitude,
                                        m_type, pod_current->sightings[i].obsid);
                            }
                    }
                }
                printf("-----------------------------------------------------\n");

            }
            pod_current = pod_current->next;
        }
    }

#ifdef	__cplusplus
}
#endif

#endif	/* FEATURE3_H */



