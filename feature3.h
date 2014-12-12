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
        //If there is something in the list
        if (*pod_list)
        {
            //Set pod_current to the head of pod linked list
            pod *pod_current = *pod_list;
            pod *pod_previous;
            //Iterate through linked list to the end
            while (pod_current)
            {
                //Set pod_previous to current and move current to next item
                pod_previous = pod_current;
                pod_current = pod_current->next;
            }
            //Assign the empty next to node
            pod_previous->next = pod_node;
        }
        else //If there's nothing in list, add something to head
        {
            *pod_list = pod_node;
        }
    }

    //Remove a sighting structure from sighting linked list
    //Takes parameters: A sighting structure, head of sighting list
    void remove_sighting(sighting *sight_node, sighting **sight_list)
    {
        //Set sight_current to the head of sighting linked list
        sighting *sight_current = *sight_list;
        sighting *sight_previous;
        //Iterate through linked list
        while(sight_current != NULL)
        {
            //If sighting structure is equal to the head of the list, don't set
            //previous to anything
            if(sight_node == *sight_list)
            {
                //Set the head of the list to the next element
                *sight_list = sight_node->next;
                //Free the sighting structure
                free(sight_node);
                return;
            }
            //If sighting structure is equal to current sighting
            else if(sight_node == sight_current)
            {
                //Set sight_previous to the next element in list
                sight_previous->next = sight_current->next;
                //Free the current sighting
                free(sight_current);
                return;
            }
            //Set sight_previous to the current sighting
            sight_previous = sight_current;
            //Move current sighting to the next element in list
            sight_current = sight_current->next;
        }
    }

    //Checks if any mammals are within a 0.1 nautical mile radius and assigns 
    //them into pods. Pods are structures in a linked list. Sightings inserted
    //into pods are contained in arrays 
    //Takes parameters: head of sighting list
    void check_pod(sighting **sight_list)
    {
        //Set sight_current to head of sighting list
        sighting *sight_current = *sight_list;
        //Instantiate two others as nothing
        struct sighting *sight_start = NULL;
        struct sighting *temp_container = NULL;
        int flag = 0;
        
        //Loop through first instance of list and copy all elements into a 
        //second list to allow deletion of elements without affecting the 
        //original list
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
            sight_copy->actual_loc.latitude = sight_current->
                    actual_loc.latitude;
            sight_copy->actual_loc.longitude = sight_current->
                    actual_loc.longitude;
            insert_sighting(sight_copy, &sight_start);
            sight_current = sight_current->next;
        }
        
        //Reset sight_current to the head of the list
        sight_current = *sight_list;
        //Set sight2_current to the head of the copied list
        sighting *sight2_current = sight_start;
        
        //Loop through original list
        while(sight_current != NULL)
        {
            //Create a new pod 
            struct pod *new_pod = make_pod();
            
            //Loop through copied list
            while(sight2_current != NULL)
            {
                //Set a temporary container to keep current sighting data intact
                temp_container = sight2_current;
                
                //Set location structure values for great_circle function
                location location_current;
                location location2_current;
                location_current.lat = sight_current->loc.latitude;
                location_current.lng = sight_current->loc.longitude;
                location2_current.lat = sight2_current->loc.latitude;
                location2_current.lng = sight2_current->loc.longitude;
                //Check distances between two location structures
                if(great_circle(location_current, location2_current) < 0.1)
                {
                    //Check the flag to prevent multiple pods from being added
                    //to the pod list
                    if(flag == 0)
                    {
                        //Insert pod to the list for this set of sightings
                        insert_pod(new_pod, &pod_start);
                        //Change flag to 1 because this pod has been made
                        flag = 1;
                    }
                    //Add current sighting to the array of sightings and 
                    //increment sighting_index to keep track of how many are in
                    new_pod->sightings[new_pod->sighting_index++] = 
                            *sight2_current;
                    //Remove the current sighting from the copied list to 
                    //prevent it from being added again
                    remove_sighting(sight2_current, &sight_start);
                }
                //Because the current sighting was removed, temp_container must
                //be used to access the next element
                sight2_current = temp_container->next;
            }
            //Reset flag to 0 to allow a pod to be inserted again
            flag = 0;
            //Reset sight2_current to head of list
            sight2_current = sight_start;
            //Move sight_current to next element in list
            sight_current = sight_current->next;
        }
    }

    //Check for mammals sighted which refer to the same mammal based on the 
    //average location found in Mission 2, and set their flag for later use
    //Takes parameters: head of pod list
    void check_duplicates(pod **pod_list)
    {
        //Set pod_current to the head of pod list
        pod *pod_current = *pod_list;
        int i, j;
        //Loop through all elements in pod list
        while(pod_current != NULL)
        {
            //Loop through all elements of the current pod array
            for(i = 0; i < pod_current->sighting_index; i++)
            {
                //Loop through all elements of the current pod array again
                for(j = 0; j < pod_current->sighting_index; j++)
                {
                    //Don't match the same element in array
                    if(j != i)
                    {
                        //If the averaged locations are the same
                        if(pod_current->sightings[i].actual_loc.latitude == 
                                pod_current->sightings[j].actual_loc.latitude && 
                                pod_current->sightings[i].actual_loc.longitude == 
                                pod_current->sightings[j].actual_loc.longitude)
                        {
                            //AND if the duplicate flag has not been set yet
                            if(pod_current->sightings[i].duplicate_flag == 0)
                            {
                                //Set the duplicate flag to true
                                pod_current->sightings[j].duplicate_flag = 1;
                            }
                        }
                    }
                }
            }
            //Move to next element in pod list
            pod_current = pod_current->next;
        }

    }

    //Prints out all pods and their mammals in designated sea area
    //Takes parameters: head of pod list
    void print_pods(pod **pod_list)
    {
        //Set pod_current to the head of pod list
        pod *pod_current = *pod_list;
        int i;
        //Keep a count of how many pods there are to label each pod
        int count = 0;
        //Keep a count of how many elements in the pod there are
        int pod_count = 0;
        char m_type[11];


        printf("LATITUDE     LONGITUDE     MAMMAL TYPE     SIGHTED BY\n");
        printf("=====================================================\n");
        //Loop through the pod list
        while(pod_current != NULL)
        {
            //Reset the pod_count each time
            pod_count = 0;
            //Loop through each element in the pods sighting array
            for(i = 0; i < pod_current->sighting_index; i++)
            {
                //Use only data within the designated sea area
                if(52.00 <= pod_current->sightings[i].loc.latitude && pod_current->
                sightings[i].loc.latitude <= 52.833 && -4.000 >= pod_current->
                sightings[i].loc.longitude && pod_current->sightings[i].loc.
                longitude >= -5.500)
                {
                    //Checks only sightings that don't have a duplicate flag
                    if(pod_current->sightings[i].duplicate_flag == 0)
                    {
                        pod_count++;
                    }
                }
            }
            //Print out only pods that have more than one mammal
            //A single mammal is not a pod
            if(pod_count > 1)
            {
                //Increment count to label each pod
                count++;
                printf("Pod %d\n", count);
                printf("-----------------------------------------------------\n");

                    //Loop through pods sighting array
                    for(i = 0; i < pod_current->sighting_index; i++)
                    {
                        //Print only data within the designated sea area
                        if(52.00 <= pod_current->sightings[i].loc.latitude && pod_current->
                        sightings[i].loc.latitude <= 52.833 && -4.000 >= pod_current->
                        sightings[i].loc.longitude && pod_current->sightings[i].loc.
                        longitude >= -5.500)
                        {
                            //Prints only sightings that don't have a duplicate 
                            //flag
                            if(pod_current->sightings[i].duplicate_flag == 0)
                            {
                                //Print out full names of mammal type
                                if(pod_current->sightings[i].mammal_type == 'D')
                                {
                                    strcpy(m_type, "Dolphin");
                                }
                                else
                                {
                                    strcpy(m_type, "Porpoise");
                                }
                                //Print each sighting data
                                printf("%-11lf %-14lf %-15s %s\n",  
                                        pod_current->sightings[i].actual_loc.latitude, 
                                        pod_current->sightings[i].actual_loc.longitude,
                                        m_type, pod_current->sightings[i].obsid);
                            }
                    }
                }
                printf("-----------------------------------------------------\n");

            }
            //Move on to next element in pod list
            pod_current = pod_current->next;
        }
    }

#ifdef	__cplusplus
}
#endif

#endif	/* FEATURE3_H */



