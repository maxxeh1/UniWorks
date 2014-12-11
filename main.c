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

/*
 * 
 */
sighting* make_sighting(char *obsid, char mammal_type, double bearing, double range);
void insert_sighting(sighting *sight_node, sighting **sight_list);
observer* make_observer(char *id, double lat, double longitude);
void insert_observer(observer *obs_node, observer **obs_list);
void print_sighting(sighting **sight_list);
void print_observer(observer **obs_list);
struct mammal_location calculate_mammal_position(double obs_lat, double obs_longitude, 
        double bearing, double range);
void apply_mammal_locations(observer **obs_list, sighting **sight_list);
void print_locations(sighting **sight_list);
void set_true_location(sighting **sight_list);
void print_locations_mission2(sighting **sight_list);
void check_pod(sighting **sight_list);
pod* make_pod();
void insert_pod(pod *pod_node, pod **pod_list);
void remove_sighting(sighting *sight_node, sighting **sight_list);
void print_pods(pod **pod_list);
double avg(double one, double two);

struct pod *pod_start = NULL;
long sighting_count = 0;

int main(int argc, char** argv) 
{
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
    
    printf("Please enter the name of the observer file: ");
    //scanf("%s", fileName);
    FILE* f1 = fopen("observers_3.txt", "r");
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
    FILE* f2 = fopen("sightings_3.txt", "r");
    while(fscanf(f2, "%4s %c %lf %lf", temp_obsid, &temp_mammal_type, 
            &temp_bearing, &temp_range) == 4)
    {
        struct sighting *new_sighting = make_sighting(temp_obsid, 
                temp_mammal_type, temp_bearing, temp_range);
        insert_sighting(new_sighting, &sighting_start);
        sighting_count++;
    }
    fclose(f2);
    print_observer(&observer_start);
    print_sighting(&sighting_start);
    
    apply_mammal_locations(&observer_start, &sighting_start);
    print_locations(&sighting_start);
    
    set_true_location(&sighting_start);
    print_locations_mission2(&sighting_start);
    
    check_pod(&sighting_start);
    print_pods(&pod_start);
}

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
        sight_current = sight_current->next;
    }
    printf("\n");
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
        if(sight_current->mammal_type == 'D')
        {
            strcpy(m_type, "Porpoise");
        }
        else
        {
            strcpy(m_type, "Dolphin");
        }
        printf("%-11lf %-14lf %-13lf %-16lf %-15s %s\n", 
                sight_current->loc.latitude, sight_current->loc.longitude, 
                sight_current->actual_loc.latitude, 
                sight_current->actual_loc.longitude, m_type, 
                sight_current->obsid);
        sight_current = sight_current->next;
    }
    printf("\n");
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

pod* make_pod()
{
    pod *node = (pod*) calloc(1, sizeof(struct pod));
    node->sightings = calloc(sighting_count, sizeof(struct sighting));
    node->next = NULL;
    node->sighting_index = 0;
    return node;
}

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

void print_pods(pod **pod_list)
{
    pod *pod_current = *pod_list;
    while(pod_current != NULL)
    {
        printf("Pod\n");
        int i;
        for(i = 0; i < pod_current->sighting_index; i++)
        {
           
            printf("%s %c %f %f\n",
                    pod_current->sightings[i].obsid,
                    pod_current->sightings[i].mammal_type,
                    pod_current->sightings[i].loc.latitude,
                    pod_current->sightings[i].loc.longitude);
        }
        pod_current = pod_current->next;
    }
}

double avg(double one, double two)
{
    double average = (one + two) / 2;
    return average;
}
