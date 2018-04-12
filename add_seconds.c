// ============================================================================
// File: add_seconds.c (Spring 2018)
// ============================================================================
// Programmer: Jennifer King
// Date: 4/11/2018
// Project: Add Seconds
// Professor: Scott Edwards
// Class: CSCI 223F | TR 4:30PM
// Description:
//  This program is an exercise in structures.  The user is prompted to enter a
//  start time in HH:MM:SS format, and also for the number of seconds to add to
//  the start time.  If all input values are legitimate, a loop is entered that
//  adds a second to the time and displays it, handling all rollovers values.
// ============================================================================

#include    <ctype.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>


// defined values
#define BUFLEN          256
#define FALSE           0
#define SLEEP_INTERVAL  1
#define TRUE            1


// structure definitions
struct Time
{
    int hours;
    int mins;
    int secs;
};

// function prototypes
void        AddOneSecond(struct Time  *timePtr);
int         GetUserTime(struct Time  *timePtr);
int         TimeIsValid(const struct Time  *timePtr);

// ==== main ==================================================================
//
// ============================================================================

int     main(void)
{
    auto    int                 counter;
    auto    int                 totalSeconds;
    auto    struct      Time    userTime;

    // get the current time from the user
    printf("Enter the start time in HH:MM:SS format: ");
    if (FALSE == GetUserTime(&userTime))
        {
        puts("Sorry, unable to read HH:MM:SS...");
        exit(EXIT_FAILURE);
        }
    else if (FALSE == TimeIsValid(&userTime))
        {
        puts("Sorry, the time you entered is invalid...");
        exit(EXIT_FAILURE);
        }

    // get how many times to loop and add seconds
    printf("How many seconds would you like to add?  ");
    if (1 != scanf("%d", &totalSeconds))
        {
        puts("Sorry, unable to read the seconds value...");
        exit(EXIT_FAILURE);
        }
    else if (totalSeconds < 0)
        {
        puts("Sorry, the seconds cannot be a negative value...\n");
        exit(EXIT_FAILURE);
        }

    // display the time
    for (counter = 0; counter < totalSeconds; ++counter)
        {
        AddOneSecond(&userTime);
        sleep(SLEEP_INTERVAL);
        printf("%02d:%02d:%02d\n", userTime.hours, userTime.mins
                                                            , userTime.secs);
        sleep(1);
        }

    puts("Time's up!!");
    return 0;

}  // end of "main"



// ==== AddOneSecond =========================================================
//
// This function increments the Time structure pointed to by the formal
// parameter by one second.  Any rollover values (seconds, minutes or hours)
// are handled appropriately.
//
// Input:
//      timePtr     -- a pointer to an initialized Time structure
//
// Output:
//      Nothing.
//
// ============================================================================

void    AddOneSecond(struct Time  *timePtr)
{
    if(timePtr -> secs == 59)
    {
        timePtr -> secs = 0;
        if(timePtr -> mins == 59)
        {
            timePtr -> mins = 0;
            if(timePtr -> hours == 24)
            {
                timePtr -> hours = 0;
            }
            else
            {
                timePtr -> hours ++;
            }
        }
        else
        {
            timePtr -> mins ++;
        }
    }
    else
    {
        timePtr -> secs ++;
    }

}  // end of "AddOneSecond"



// ==== GetUserTime ===========================================================
//
// This function reads a formatted time string from stdin and stores it in the
// formal parameter. In order for the extraction to be considered successful,
// it must be read in HH:MM:SS format. This function only reads the values into
// the structure parameter, it does not validate each field to make sure that
// they are within valid ranges.
//
// Input:
//      timePtr     -- a pointer to a Time structure
//
// Output:
//      A value of TRUE if the time is successfully read from stdin and stored
//      in the caller's argument, FALSE otherwise.
//
// ============================================================================

int     GetUserTime(struct Time  *timePtr)
{
    if(1 == scanf("%02d:%02d:%02d", &timePtr -> hours, &timePtr -> mins, &timePtr -> secs))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }


}  // end of "GetUserTime"



// ==== TimeIsValid ===========================================================
//
// This function checks to see if the structure pointed to by the formal
// parameter contains valid values or not. If any of the fields are invalid,
// a value of FALSE is returned, otherwise a value of TRUE is returned.
//
// Input:
//      timePtr     -- a pointer to an initialized Time structure
//
// Output:
//      A value of TRUE if the time parameter contains only legal values,
//      FALSE otherwise.
//
// ============================================================================

int         TimeIsValid(const struct Time  *timePtr)
{
    if(timePtr -> hours > 24 || timePtr -> hours < 0 || timePtr -> mins > 59
    || timePtr -> mins < 0 || timePtr -> secs > 59 || timePtr -> secs < 0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}  // end of "TimeIsValid"

