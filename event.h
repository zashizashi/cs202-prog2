/**************************************
Daniel Trang
CS202: Programming Systems
Program #2
Event Header File

This file contains the base class Event and its
derived classes Meeting, To-Do, and Task.
The Event class is the HUB where I've defined
virtual keywords for all the functions shared
by its children. 
**************************************/
#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <cstring>
using namespace std;

//base class calendar event
class event 
{
    public:
        event();
        event(const event& src_event);
        event(const char* src_title);
        virtual ~event();
       
        //set and get next, and helper functions
        event*& getNext();  //to manage LLL from client-side
        bool setNext(event* ptr_copy); //to manage LLL from client-side
        int peek_todo();   //returns is_a_todo int value
        bool compare_name(char* to_compare);  //cstring compare names 


        //client can call these functions
        virtual bool set_new();    //each add function is different for derived
        virtual bool display();  //displays event private data, diff for derived
        virtual bool mark_complete();   //marks event complete, bool=true
        
        //virtual functions used to manage To-Do's LLL
        virtual bool remove_todo(char* to_remove); //non To-Do obj execute default
        virtual bool remove_todo_all();  //non To-Do obj execute default call here
        
        
    protected:
        bool set_title(char* src_title);  //helper function
        bool is_complete();  //returns bool complete
        char* get_title();   //returns event title
        bool mark_todo();   //flag 0 or 1 int is_a_todo

    private:
        char* title;   //title data used by all derived
        bool complete;   //used by all derived, marks if event is complete or not
        event* next;   //to link to next event and make LLL
        int is_a_todo;  //flag 0 = not a To-Do, 1 = is a To-Do
};



//meetings have fixed time frames, location, and people attending
class meeting: public event
{
    public:
        meeting();
        meeting(const meeting& src_meeting);
        ~meeting();
        
        bool set_new(); //prompts user for input to set private data members
        bool display(); //displays private members in a simple format
        bool mark_complete();  //check-in statement confirming attendance

    private:
        char* location;   //could be a zoom id, online link, or actual address
        char* description;   //detail info about the meeting
        char* attendees;   //people who are attending the meeting
        char* from_time;
        char* till_time; 
};


//tasks have a set deadline, and are overdue after that date
class task: public event
{
    public:
        task();
        task(const task& src_task);
        ~task();

        bool set_new();
        bool display();
        bool mark_complete();  //displays on-time statement

    private:
        char* deadline;
};



//to do list is simply a list of things to do with no real deadline
class todo: public event
{
    public:
        todo();
        todo(const todo& src_todo);
        todo(const char* src_list_name);
        ~todo();

        bool set_new(); //adds new node at head of LLL

        bool display();  //wrapper function to call recursive display from
        bool display(todo* curr); //recursively displays LLL of todo items

        bool mark_complete();  //encouraging words of congradulations
        bool mark_complete(char* to_complete, todo* curr); //recursive find + mark todo in LLL

        bool remove_todo(char* to_remove); //wrapper function to call remove
        bool remove_todo(char* to_remove, todo* curr, todo* to_delete); //deletes once
        bool remove_todo_all(); //wrapper function call recursive remove all
        bool remove_todo_all(todo* curr);  //deletes entire todo LLL
        
    private: 
        todo* next;   //next ptr to a LLL of todo things
};
#endif
