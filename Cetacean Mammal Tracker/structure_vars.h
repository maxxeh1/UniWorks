/* 
 * File:   observer_vars.h
 * Author: maxxeh
 *
 * Created on 04 December 2014, 20:53
 */

#ifndef OBSERVER_VARS_H
#define	OBSERVER_VARS_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Variables for global use
    struct pod *pod_start = NULL;
    long sighting_count = 0;
    
    //Structure to hold date and time from Observer File
    struct dateTime{
        int hour;
        int minute;
        int second;
        int date;
        int month;
        int year;
    } dateTime;
    
    //Structure to hold observers from Observer File
    typedef struct observer{
        char id[21];
        double lat;
        double longitude;
        struct observer *next; //Pointer to next element in list
    } observer;

    //Structure to hold latitude and longitude variables for sightings
    typedef struct mammal_location{
        double latitude;
        double longitude;
    } mammal_location, actual_location;

    //Structure to hold sightings from Sightings File
    typedef struct sighting{
        char obsid[21];
        char mammal_type;
        double bearing;
        double range;
        struct sighting *next; //Pointer to next element in list
        struct mammal_location loc; //Holds calculated lat and long data
        struct mammal_location actual_loc; //Holds averaged lat and long data
        int duplicate_flag; //Flag to show the structure is a duplicate element
    } sighting;

    //Structure to hold pods
    typedef struct pod{
        struct pod *next; //Pointer to next element in list
        struct sighting *sightings; //Pointer to sightings array
        int sighting_index; //Number of sightings in sightings array
    } pod;
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* OBSERVER_VARS_H */

