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

    struct dateTime{
        int hour;
        int minute;
        int second;
        int date;
        int month;
        int year;
    } dateTime;

    typedef struct observer{
        char id[21];
        double lat;
        double longitude;
        struct observer *next;
    } observer;
    
    typedef struct mammal_location{
        double latitude;
        double longitude;
    } mammal_location;
    
    typedef struct actual_location{
        double latitude;
        double longitude;
    } actual_location;
    
    typedef struct sighting{
        char obsid[21];
        char mammal_type[1];
        double bearing;
        double range;
        struct sighting *next;
        struct mammal_location loc;
        struct mammal_location actual_loc;
    } sighting;
    
    typedef struct pod{
        struct pod *next;
        struct sighting *start;
    } pod;
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* OBSERVER_VARS_H */

