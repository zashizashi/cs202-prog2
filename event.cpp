/**************************************
Daniel Trang
CS202: Programming Systems
Program #2
Event Header File

This file contains the implementation of
base class Event and its derived classes 
Meeting, To-Do, and Task. The Event class 
is the HUB where I've defined virtual keywords 
for all the functions shared by its children. 

The 5 key important functions here are:
add, remove, retrieve, delete all, and display.
All of these functions perform slightly different
depending on which derived class calls the
fucntion. They will all be called through
the base class thanks to keyword Virtual.
**************************************/
#include "event.h"


/* EVENT CLASS IMPLEMEMNTATION */
event::event(): title(nullptr), complete(false), next(nullptr), is_a_todo(0){}


event::event(const event& src_event)
{
    set_title(src_event.title);
	complete = src_event.complete;
	next = src_event.next;
    is_a_todo = src_event.is_a_todo;
}


event::event(const char* src_title)
{
    this->title = new char[strlen(src_title)+1];
    strcpy(this->title, src_title);
}


event::~event()
{
	if(this->title)
	{
		delete []title;
	}
    title = nullptr;

	if(next)
	{
		delete next;
	}
    next = nullptr;

    complete = false;
}


event*& event::getNext()
{
	return this->next;
}


bool event::setNext(event* ptr_copy)
{
	//sets this next ptr to a passed in ptr address, ptr_copy can be a null pointer
	this->next = ptr_copy;
	return true;
}


int event::peek_todo()
{
    return is_a_todo;
}


bool event::set_title(char* src_title)
{
    this->title = new char[strlen(src_title)+1];
    strcpy(this->title, src_title);
    return true;
}


bool event::compare_name(char* to_compare)
{
    if(strcmp(this->title, to_compare) == 0)
        return true;

    return false;
}


bool event::is_complete()
{
    return complete;
}


char* event::get_title()
{
    return title;
}


bool event::set_new()
{
	char new_title[100];

	cout<<"Enter event name: ";
	cin.get(new_title, 100);
    cin.ignore();

    set_title(new_title);
	return true;
}


bool event::mark_complete()
{
    this->complete = true;
    return true;
}


bool event::display()
{
	if(title == nullptr)
	{
		cout<<"[Empty Title]"<<endl;
		return false;
	}

    if(complete == true)
    {
        cout<<"["<<title<<"] [X]"<<endl;
    }
    else
    {
        cout<<"["<<title<<"] [ ]"<<endl;
    }
	return true;
}


bool event::remove_todo(char* to_remove)
{
    cout<<"Oopsies, you're not a To-Do object. Why are you calling this function?"<<endl;
    return false;
}


bool event::remove_todo_all()
{
    cout<<"Oopsies, you're not a To-Do object. Why are you calling this function?"<<endl;
    return false;
}


bool event::mark_todo()
{
    is_a_todo = 1;
    return true;
}


//########################################################################

/* MEETING CLASS IMPLEMENTATION */
meeting::meeting(): location(nullptr), description(nullptr), attendees(nullptr), from_time(nullptr), till_time(nullptr){}


meeting::meeting(const meeting& src_meeting): event(src_meeting)
{
	this->location = new char[strlen(src_meeting.location)+1];
	strcpy(this->location, src_meeting.location);

	this->description = new char[strlen(src_meeting.description)+1];
	strcpy(this->description, src_meeting.description);

	this->attendees = new char[strlen(src_meeting.attendees)+1];
	strcpy(this->attendees, src_meeting.attendees);

	this->from_time = new char[strlen(src_meeting.from_time)+1];
	strcpy(this->from_time, src_meeting.from_time);

    this->till_time = new char[strlen(src_meeting.till_time)+1];
    strcpy(this->till_time, src_meeting.till_time);
}


meeting::~meeting()
{
	if(location)
	{
		delete []location;
		location = nullptr;
	}

	if(description)
	{
		delete []description;
		description = nullptr;
	}

	if(attendees)
	{
		delete []attendees;
		attendees = nullptr;
	}

    if(from_time)
    {
        delete []from_time;
        from_time = nullptr;
    }

    if(till_time)
    {
        delete []till_time;
        till_time = nullptr;
    }
}


bool meeting::set_new()
{
	int MAX_CHAR = 100;
	char input_description[500];
    char input_name[MAX_CHAR];
	char input_location[MAX_CHAR], input_from_time[MAX_CHAR];
    char input_till_time[MAX_CHAR], input_attendees[MAX_CHAR];


    //User input here
    cout<<"Enter meeting name: ";
    cin.get(input_name, MAX_CHAR);
    cin.ignore();

	cout<<"Meeting location: ";
	cin.get(input_location, MAX_CHAR);
	cin.ignore();

	cout<<"Meeting description (max 500 char): ";
	cin.get(input_description, 500);
	cin.ignore();

	cout<<"Who's attending?: ";
	cin.get(input_attendees, MAX_CHAR);
    cin.ignore();

	cout<<"When does the meeting start? (ex. 11:45am): ";
	cin.get(input_from_time, MAX_CHAR);
    cin.ignore();

    cout<<"When does the meeting end? (ex. 7:30pm): ";
    cin.get(input_till_time, MAX_CHAR);
    cin.ignore();

    //set Base private member title using Base function
    event::set_title(input_name);
    
    //Allocating new mem for user inputs
	this->location = new char[strlen(input_location)+1];
	strcpy(this->location, input_location);

	this->description = new char[strlen(input_description)+1];
	strcpy(this->description, input_description);

	this->attendees = new char[strlen(input_attendees)+1];
	strcpy(this->attendees, input_attendees);

	this->from_time = new char[strlen(input_from_time)+1];
	strcpy(this->from_time, input_from_time);

	this->till_time = new char[strlen(input_till_time)+1];
	strcpy(this->till_time, input_till_time);

    return true;
}


bool meeting::display()
{
    cout<<"\n";
    cout<<"      MEETING\n";
    cout<<"--------------------"<<endl;

    //Base display()
	event::display();

    //Display Meeting private members
	cout<<"Location: "<<location<<endl;
	cout<<"Time: "<<from_time<<" to "<<till_time<<endl;
	cout<<"Attendees: "<<attendees<<endl;
	cout<<"\n"<<description<<"\n"<<endl;
	return true;
}


bool meeting::mark_complete()
{
    cout<<"You have checked-in and attended ["<<get_title()<<"]"<<endl;
    event::mark_complete();
    return true;
}

//#############################################################

/* TASK IMPLEMENTATION */
task::task(): deadline(nullptr){}

task::task(const task& src_task): event(src_task)
{
    this->deadline = new char[strlen(src_task.deadline)+1];
    strcpy(this->deadline, src_task.deadline);
}

task::~task()
{
    if(deadline)
    {
        delete []deadline;
        deadline = nullptr;
    }
}

bool task::set_new()
{
    int MAX_CHAR = 100;
    char input_name[MAX_CHAR], input_deadline[MAX_CHAR];

    //Ask for name of task
    cout<<"Enter task name: ";
    cin.get(input_name, MAX_CHAR);
    cin.ignore();

    //Ask for user deadline
    cout<<"What's the deadline for this task?(ex. 11:59pm): ";
    cin.get(input_deadline, MAX_CHAR);
    cin.ignore();
   
    //set name of task through Base constructor
    event::set_title(input_name);

    //set private member "deadline"
    this->deadline = new char[strlen(input_deadline)+1];
    strcpy(this->deadline, input_deadline);

    return true;
}

bool task::display()
{
    cout<<"\n";
    cout<<"       TASK\n";
    cout<<"--------------------"<<endl;
    
    //Base display function
    event::display();

    //Display Task
    cout<<"Deadline: "<<deadline<<endl;
    return true;
}


bool task::mark_complete()
{
    cout<<"["<<get_title()<<"] completed on-time. +15 pts for Raven Claw!"<<endl;
    event::mark_complete();
    return true;
}


//###############################################################


/* TO DO IMPLEMENTATION */
todo::todo(): next(nullptr)
{
    event::mark_todo(); //ALWAYS mark a new To-Do object with flag = 1
}


//copies only node todo node
todo::todo(const todo& src_todo): event(src_todo)
{
    if(src_todo.next != nullptr)
    {
        next = new todo(*(src_todo.next));
    }
}


todo::todo(const char* src_list_name): event(src_list_name), next(nullptr){}


todo::~todo()
{
    if(next)
    {
        delete next;
    }
    next = nullptr;
}


//this builds the To-Do LLL
bool todo::set_new()
{
    char src_list_name[100];

    cout<<"Enter a new To-Do item: ";
    cin.get(src_list_name, 100);
    cin.ignore();

    //if root node does not have a head ptr
    if(next == nullptr)
    {
        next = new todo(src_list_name);
        return true;
    }
    else
    {
        todo* save = next;   //saves old head of LLL
        next = new todo(src_list_name); //updates head to some new
        next->next = save;   //new head next points to old head of LLL
        return true;
    }
    return false; //reaches end of function without creating node
}


bool todo::display()
{
   if(next == nullptr)
   {
       cout<<"To-Do list is empty."<<endl;
       return false;
   }
   cout<<"\n";
   cout<<"    TO-DO LIST\n";
   cout<<"--------------------"<<endl;
   return display(next);
}

bool todo::display(todo* curr)
{
    if(curr != nullptr)
    {
        curr->event::display();
        display(curr->next);
    }
    return true;
}


bool todo::mark_complete()
{
    if(next == nullptr)
    {
        cout<<"To-Do list is empty."<<endl;
        return false;
    }

    char to_complete[100];
    cout<<"Enter the To-Do item to mark complete: ";
    cin.get(to_complete, 100);
    cin.ignore();

    return mark_complete(to_complete, next); 
}

bool todo::mark_complete(char* to_complete, todo* curr)
{
    if(curr != nullptr)
    {
        if(curr->compare_name(to_complete) == true)
        {
            cout<<"You completed ["<<curr->get_title()<<"]. Here's a cookie!"<<endl;
            curr->event::mark_complete();
            return true;
        }
        return mark_complete(to_complete, curr->next);
    }

    //Reached end of LLL
    cout<<"Could not find To-Do item of that name."<<endl;
    return false;
}


bool todo::remove_todo(char* to_remove)
{
    if(next == nullptr)
    {
        cout<<"To-Do list is empty."<<endl;
        return false;
    }

    //If first node in LLL is to be deleted
    if(next->compare_name(to_remove) == true)
    {
        todo* save = next->next; //saves 2nd node in LLL 
        next->next = nullptr; //break link between next and LLL
        delete next; //deletes next and everything it connects to
        next = save; //set empty next to save which holds 2nd node
        return true;
    }

    //Else run the recursive find/delete
    todo* to_delete = next->next; //to_delete is one node ahead
    return remove_todo(to_remove, next, to_delete);
}

bool todo::remove_todo(char* to_remove, todo* curr, todo* to_delete)
{
    if(to_delete != nullptr)
    {
        if(to_delete->compare_name(to_remove) == true)
        {
            curr->next = to_delete->next;
            to_delete->next = nullptr;
            delete to_delete;
            return true;
        }
        return remove_todo(to_remove, curr->next, to_delete->next);
    }

    //Reached end of list
    cout<<"["<<to_remove<<"] was not found in this To-Do list."<<endl;
    return false;
}


bool todo::remove_todo_all()
{
   if(next == nullptr)
   {
       cout<<"To-Do list is empty."<<endl;
       return false;
   }
    
   remove_todo_all(next);
   delete next;
   next = nullptr;

   return true;
}

bool todo::remove_todo_all(todo* curr)
{
    if(curr->next->next != nullptr)
    {
        remove_todo_all(curr->next);
    }
    delete curr->next; 
    curr->next = nullptr;
    return true;
}
