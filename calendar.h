/**************************************
Daniel Trang
CS202: Programming Systems
Program #2
Calendar Header File

This file contains the building blocks of
the Doubly Linked List which is of type
Calendar Days. Each node will represent a day
of the week up to 7 days (this will be determined
by a static integer or from data.txt file).

Full implementation of this DLL will include add,
remove, retrieve, delete all, and display.

Other functions include wrapper functions which
will help call to another hierarchy called Event.
Functions include adding new event, remove event,
retrieve event, and delete all events. These
functions will only affect the current Day of the
Calendar.
**************************************/
#ifndef CALENDAR_H
#define CALENDAR_H
#include "event.h"


//base class calendar
class calendar
{
    public:
        calendar();
        calendar(char* input_day, int input_date);
        calendar(const calendar& src_calendar);
        ~calendar();

        
        //functions managing DLL of calendar days
        bool add_new_day();
        bool remove_day();
        bool remove_all_days();
        bool retrieve_day(calendar& pass_back); //user sends in an object to copy to
        bool display_all_days();
        bool display_one();  //displays out one object by reference

       
        //functions managing Event LLL
        bool add_event(); //wrapper function to call recursive find + add_event
        bool remove_event();    //wrapper function to remove specific event by name
        bool retrieve_event(event& user_obj); //passes back obj reference of event if found
        bool delete_all_events();   //removes all events in the current Day
        bool display_events();         

    protected:
        //Calendar DLL functions
        bool add_new_day(char* input_day, int input_date, calendar* curr);
        bool remove_day(char* to_remove, calendar* curr, calendar* to_delete);
        bool remove_all_days(calendar* curr);
        bool display_all_days(calendar* curr); 
        bool retrieve_day(char* to_retrieve, calendar& pass_back, calendar* curr);

        //Event LLL functions
        bool add_existing_todo(event* curr);  //looks for To-Do node and sets found to same address
        bool add_event(char* find, calendar* curr); //finds correct day to add to 
        bool add_new_event();   //user calls this to add new event in a day
        bool remove_event(char* find, calendar* curr);
        bool remove_one_event();
        bool remove_one_event(char* event_name, event* curr, event* to_delete); //recursive helper function
        bool remove_all_events(event* curr);
        bool delete_all_events(calendar* curr);
        bool display_events(calendar* curr); //recursively find day to display
        bool display_all_events();  //displays all events in the current Day
        bool display_all_events(event* curr); //recursive helper function for display
        bool copy(calendar& src_calendar);  //copys day obj 
        
    private:
        char* day;  //name of the Day (ex. Wednesday)
        int date;  //numerical date of the Day (ex. 1,2,3, ... , 31)
        calendar* calendar_day;  //base pointer to entire DLL of days
        calendar* previous; //previous and next pointers to Days
        calendar* next;   //previous and next pointers to Days
        event* event_list;   //base class pointer to Event class, this points to any Event hierarchy
};


//Another level of abstraction for the User
//derived class User
class user: public calendar
{
    public:
        user();
        user(const user& src_user);
        ~user();

        int main_program();
        char user_menu();
        bool execute(char user_input);
        bool continue_menu();
        
    private:
        char* user_name;
};
#endif
