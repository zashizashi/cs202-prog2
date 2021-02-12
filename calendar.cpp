/**************************************
Daniel Trang
CS202: Programming Systems
Program #2
Calendar Implementation File

This file is split into two main parts.
The first part is all the functions and
constructors that belong to managing the
DLL of calendar Days.
The second part is a section dedicated to
functions managing the Event LLL.

For each of the functions (add, remove,
display, retrieve, remove all), there are
wrapper functions. The purpose of these
wrapper functions are to call the current
object's private pointers. This creates
a new level of abstraction to "hide" the
User from messing around with ANY private
data members belonging to this program.
**************************************/
#include "calendar.h"

/* BASE CLASS CALENDAR IMPLEMENTATION */
calendar::calendar(): day(nullptr), date(0), calendar_day(nullptr), previous(nullptr), next(nullptr), event_list(nullptr){}


calendar::calendar(char* input_day, int input_date)
{
    this->day = new char[strlen(input_day)+1];
    strcpy(this->day, input_day);

    date = input_date;
}


calendar::calendar(const calendar& src_calendar): calendar_day(nullptr), previous(nullptr), next(nullptr)
{
    //Calendar private members
    if(src_calendar.day)
    {
        this->day = new char[strlen(src_calendar.day)+1];
        strcpy(this->day, src_calendar.day);
    }
    date = src_calendar.date;

    //private Data Structure pointers
    if(src_calendar.event_list)
    {
        event_list = new event(*(src_calendar.event_list));
    }
}


calendar::~calendar()
{
    if(day)
        delete []day;
    day = nullptr;
    
    if(calendar_day)
        delete calendar_day;
    calendar_day = nullptr;

    if(previous)
        delete previous;
    previous = nullptr;

    if(next)
        delete next;
    next = nullptr;

    if(event_list)
        delete event_list;
    event_list = nullptr;
}


//The next few functions are purely to manage the DLL of Calendar Days
//Note that the first calendar 'node' (the user currently IS the first node)
//contains a calendar_month ptr to the actual DLL as well as prev, next ptrs
//the user's prev, next should NEVER point to anything, only to be used by DLL

bool calendar::add_new_day()
{
    int max = 100, input_date = 0;
    char input_day[max];     

    cout<<"Enter the day (ex. Friday): ";
    cin.get(input_day, max);
    cin.ignore(1000, '\n');

    cout<<"Enter the date (ex. 1, 2, 3, ..., 31): ";
    cin>>input_date;
    cin.ignore(1000, '\n');

    //if DLL of days does not exist yet
    if(calendar_day == nullptr)
    {
        calendar_day = new calendar(input_day, input_date);
        return true;
    }
    else
    {
        //if new day is earlier than existing days, add to front
        if(input_date < calendar_day->date)
        {
            calendar* save = calendar_day;
            calendar_day = new calendar(input_day, input_date);
            calendar_day->next = save;
            save->previous = calendar_day;
            return true;
        }

        //if new day is equal to the first day in DLL, do not add
        if(input_date == calendar_day->date)
        {
           cout<<"Duplicate date found. Cannot add two of the same date."<<endl;
           return false;
        }

        //if new day is later than first day in the DLL, insert by recursion
        if(input_date > calendar_day->date)
        {
            //recursion call add day here, where calendar_day is the head of DLL
            return add_new_day(input_day, input_date, calendar_day);
        }
    }
    return false; //reache end of function without creating node 
}

bool calendar::add_new_day(char* input_day, int input_date, calendar* curr)
{
    if(curr != nullptr)
    {
        //if found matching dates, duplicates cannot be allowed
        if(input_date == curr->date)
        {
            cout<<"Duplicate date found. Cannot add two of the same date."<<endl;
            return false;
        }

        //if date is smaller than current, add node before current
        if(input_date < curr->date)
        {
            calendar* new_day = new calendar(input_day, input_date);
            new_day->next = curr;
            new_day->previous = curr->previous;
            new_day->previous->next = new_day;
            curr->previous = new_day;
            return true;
        }
        
        //add node after curr if date greater than current date AND we've reached the end of DLL
        if(input_date > curr->date && curr->next == nullptr)
        {
            calendar* new_day = new calendar(input_day, input_date);
            new_day->previous = curr;
            curr->next = new_day;
            return true;
        }
        //keep recursing through DLL
        return add_new_day(input_day, input_date, curr->next);
    }

    //Reached end of DLL
    cout<<"An error occurred trying to insert new Day ["<<input_date<<"]"<<endl;
    return false;
}


bool calendar::remove_day()
{
    if(calendar_day == nullptr)
    {
        cout<<"There are no days to remove."<<endl;
        return false;
    }

    char to_remove[100];
    cout<<"Which day do you want to remove?(ex. Monday): ";
    cin.get(to_remove, 100);
    cin.ignore(1000, '\n');

    //If first node is to be removed
    if(strcmp(calendar_day->day, to_remove) == 0)
    {
        calendar* save = calendar_day->next; //save 2nd node
        if(save != nullptr)
        {
            save->previous = nullptr; //2nd node prev is now null
        }
        calendar_day->next = nullptr; //detach head from DLL
        delete calendar_day;  //delete head
        calendar_day = save;  //head equals 2nd node
        return true;
    }

    //recursively find to delete day
    calendar* to_delete = calendar_day->next; //to_delete is head->next
    return remove_day(to_remove, calendar_day, to_delete);
}

bool calendar::remove_day(char* to_remove, calendar* curr, calendar* to_delete)
{
    if(to_delete != nullptr)
    {
        //if to delete is a middle node
        if(strcmp(to_delete->day, to_remove) == 0 && to_delete->next != nullptr)
        {
            curr->next = to_delete->next;
            to_delete->next->previous = curr;
            to_delete->next = nullptr;
            to_delete->previous = nullptr;
            delete to_delete;
            return true;
        }
        //if to delete is the last node in DLL
        if(strcmp(to_delete->day, to_remove) == 0 && to_delete->next == nullptr)
        {
            curr->next = nullptr;
            to_delete->previous = nullptr;
            delete to_delete;
            to_delete = nullptr;
            return true;
        }
        
        //continue recursing till node is found
        return remove_day(to_remove, curr->next, to_delete->next);
    }

    //Reached end of DLL
    cout<<"Could not find day ["<<to_remove<<"]"<<endl;
    return false;
}


bool calendar::remove_all_days()
{
    if(calendar_day == nullptr)
    {
        cout<<"There are no days to remove."<<endl;
        return false;
    }

    //recursively delete all days in DLL
    remove_all_days(calendar_day);
    calendar_day = nullptr;
    return true;
}

bool calendar::remove_all_days(calendar* curr)
{
    if(curr != nullptr)
    {
        calendar* temp = curr->next;
        curr->next = nullptr;
        delete curr;
        curr = temp;
        if(curr == nullptr)
        {
            return true;
        }
        curr->previous = nullptr;
        return remove_all_days(curr); 
    }
    return true;
}


bool calendar::retrieve_day(calendar& pass_back)
{
    if(calendar_day == nullptr)
    {
        cout<<"There are no days. Please create one first."<<endl;
        return false;
    }

    char to_retrieve[100];
    cout<<"Which day do you want to retrieve?: ";
    cin.get(to_retrieve, 100);
    cin.ignore(1000, '\n');

    return retrieve_day(to_retrieve, pass_back, calendar_day);
}

bool calendar::retrieve_day(char* to_retrieve, calendar& pass_back, calendar* curr)
{
    if(curr != nullptr)
    {
        if(strcmp(curr->day, to_retrieve) == 0)
        {
            pass_back.copy(*curr);  //problematic...
            return true;
        }
        return retrieve_day(to_retrieve, pass_back, curr->next);
    }
    return false;
}


bool calendar::display_all_days()
{
    if(calendar_day == nullptr)
    {
        cout<<"There are no days. Please create one first."<<endl;
        return false;
    }

    return display_all_days(calendar_day); 
}

bool calendar::display_all_days(calendar* curr)
{
    if(curr != nullptr)
    {
        cout<<" ---------------"<<endl;
        cout<<"    "<<curr->day<<" "<<curr->date<<endl;
        cout<<" ---------------"<<endl;
        display_all_days(curr->next);
    }
    return true;
}

bool calendar::copy(calendar& src_calendar)
{
    //Calendar private members
    if(src_calendar.day)
    {
        this->day = new char[strlen(src_calendar.day)+1];
        strcpy(this->day, src_calendar.day);
    }
    date = src_calendar.date;

    //private Data Structure pointers
    if(src_calendar.event_list)
    {
        cout<<"Haha.. I forgot to write virtual copy functions in the event hierarchy\n";
        cout<<"and I'm not going to do it."<<endl;
    }
    return true;
}


bool calendar::display_one()
{
    cout<<day<<" "<<date<<endl;
    if(event_list)
    {
        this->display_events();
    }
    return true;
}


//The next few functions are purely to manage the LLL of Events
//The event* pointer (event_list) directly points to the head of the LLL
//Only called by Calendar day nodes, User never uses it's event pointer

bool calendar::add_event()
{
    if(calendar_day == nullptr)
    {
        cout<<"Create a new day first before adding an event."<<endl;
        return false;
    }

    char find[100];
    cout<<"Which day do you want to add a new Event to?(ex. Monday): ";
    cin.get(find, 100);
    cin.ignore(1000, '\n');

    return add_event(find, calendar_day);
}

bool calendar::add_event(char* find, calendar* curr)
{
    if(curr != nullptr)
    {
        if(strcmp(curr->day, find) == 0)
        {
            curr->add_new_event();
            return true;
        }

        return add_event(find, curr->next);
    }

    //Reached end of DLL
    cout<<"Could not find day ["<<find<<"]"<<endl;
    return false;
}

bool calendar::add_new_event()
{
	bool good_input = false;
	char user_input;

    //Ask for User input in a while loop till User input is 'good'
	while(good_input == false)
	{
		cout<<"What kind of event would you like to create?\n";
		cout<<"1. Add a new Meeting\n";
		cout<<"2. Add a new To-Do\n";
		cout<<"3. Add a new Task\n"<<endl;
        cout<<"Enter the number of the option you wish to select: ";
        cin>> user_input;
        cin.ignore();

		if(user_input == '1' || user_input == '2' || user_input == '3')
		{
			good_input = true;	//breaks the while loop
		}
		else
		{
			cout<<"Invalid input. Please try again."<<endl;
		}
	}

    //Node created and upcasted to correct derived type, prompt User to set node data 
    event* save = event_list; //saves ptr to head of pre-existing event list if any
	switch(user_input)
    {
		case '1':
			event_list = new meeting;	//upcasts + creates new obj derived Meeting
            event_list->set_new(); //call derived function by RTTI through virtual keyword
            event_list->setNext(save);  //event list becomes new head node, pointing to save 
			break;

		case '2':
            if(add_existing_todo(event_list) == true)
            {
                cout<<"Adding new todo to existing list..."<<endl; 
            }
            else
            {
                event_list = new todo;	//upcasts + creates new obj derived To-Do
                event_list->set_new(); //call derived function by RTTI through virtual keyword
                event_list->setNext(save);  //event list becomes new head node, pointing to save 
            }
            break;

		case '3':
			event_list = new task;	//upcasts + creates new obj derived Task
            event_list->set_new(); //call derived function by RTTI through virtual keyword
            event_list->setNext(save);  //event list becomes new head node, pointing to save 
			break;
    }
    return true;
}


bool calendar::remove_event()
{
    if(calendar_day == nullptr)
    {
        cout<<"There are no days. Please make one first."<<endl;
        return false;
    }

    char find[100];
    cout<<"Which day do you want to remove an Event from?: ";
    cin.get(find, 100);
    cin.ignore(1000, '\n');

    return remove_event(find, calendar_day);
}

bool calendar::remove_event(char* find, calendar* curr)
{
    if(curr != nullptr)
    {
        if(strcmp(curr->day, find) == 0)
        {
            curr->remove_one_event();
            return true;
        }
        return remove_event(find, curr->next);
    }
    cout<<"Could not find event of name ["<<find<<"]"<<endl;
    return false;
}

bool calendar::remove_one_event()
{
    if(event_list == nullptr)
    {
        cout<<"There are no events this day ["<<day<<" "<<date<<"]"<<endl;
        return false;
    }

    //Ask user which event to delete by name
    char event_name[100];
    cout<<"Enter name of Event to delete: ";
    cin.get(event_name, 100);
    cin.ignore();

    //If first node in event LLL is to be deleted
    if(event_list->peek_todo() == 0)
    {
        if(event_list->compare_name(event_name) == true)
        {
            event* save = event_list->getNext();
            event_list->setNext(nullptr);
            delete event_list;
            event_list = save;
        }
        return true;
    }

    //If first node in event LLL is To-Do
    if(event_list->peek_todo() == 1)
    {
        //if To-Do node is empty, set head to next node in LL
        if(event_list->remove_todo(event_name) == false)
        {
            event* save = event_list->getNext();
            event_list->setNext(nullptr);
            delete event_list;
            event_list = save;
        }
        return true;
    }
    
    //else recursively find to delete
    event* to_delete = event_list->getNext();
    return remove_one_event(event_name, event_list, to_delete);
}

bool calendar::remove_one_event(char* event_name, event* curr, event* to_delete)
{
   if(to_delete != nullptr)
   {
       //if we found a To-Do node, call its special remove function
       if(to_delete->compare_name(event_name) == true && to_delete->peek_todo() == 1)
       {
           //If the To-Do node is already empty, remove it from event LLL
           //else, the To-Do remove function has called correctly
           if(to_delete->remove_todo(event_name) == false)
           {
               curr->setNext(to_delete->getNext());
               to_delete->setNext(nullptr); //superfluous, but safe
               delete to_delete;
               return true;
           }
       }
       //if we found a Meeting or Task, remove node normally
       if(to_delete->compare_name(event_name) == true && to_delete->peek_todo() == 0)
       {
           curr->setNext(to_delete->getNext());
           to_delete->setNext(nullptr);
           delete to_delete;
           return true;
       }

       //the node has not yet been found, then call recursive again
       return remove_one_event(event_name, curr->getNext(), to_delete->getNext());
   }

   //Reached end of event LLL
   cout<<"["<<event_name<<"] was not found in today's event list."<<endl;
   return false;
}


bool calendar::delete_all_events()
{
    if(calendar_day == nullptr)
    {
        return false;
    }

    return delete_all_events(calendar_day);
}

bool calendar::delete_all_events(calendar* curr)
{
    if(curr != nullptr)
    {
        curr->remove_all_events(curr->event_list);
        curr->event_list = nullptr;
        return delete_all_events(curr->next);
    }
    return true;
}

bool calendar::remove_all_events(event* curr)
{
    if(curr == nullptr)
    {
        return false;
    }

    if(curr->getNext() != nullptr)
    {
        return remove_all_events(curr->getNext());
    }

    if(curr->peek_todo() == 0)
    {
        delete curr;
        return true;
    }
    else  //current is a todo
    {
        curr->remove_todo_all();
        delete curr;
        return true;
    }
    return false;  //somehow reaches end of function
}


/*
bool calendar::retrieve_event(event& user_obj)
{
	int MAX_CHAR = 100;
	char find_this[MAX_CHAR];

	//Asks user for name of Event to delete
	cout<<"Enter the name of the Event to retrieve: ";
	cin.get(find_this, MAX_CHAR);

	//while 
	while(event_list->compare_title(find_this) != true && event_list->getNext() != nullptr)
	{
		event_list = event_list->getNext();
	}

	if(event_list->getNext() == nullptr)
	{
		cout<<"Event ["<<find_this<<"] was not found."<<endl;
		return false;
	}

	user_obj = *event_list;	//pass back Event object to user
	return true;
}
*/


bool calendar::display_events()
{
    if(calendar_day == nullptr)
    {
        cout<<"Try adding a new day first before calling display."<<endl;
        return false;
    }
    return display_events(calendar_day);
}

bool calendar::display_events(calendar* curr)
{
    if(curr != nullptr)
    {
        curr->display_all_events();
        return display_events(curr->next);
    }

    return true;
}

bool calendar::display_all_events()
{
    if(event_list == nullptr)
    {
        cout<<"\n"<<endl;
        cout<<"========================"<<endl;
        cout<<"         "<<day<<" "<<date<<endl;
        cout<<"========================"<<endl;
        cout<<"   [EMPTY LIST]"<<endl;
        cout<<"\n"<<endl;
        return false;
    }

    cout<<"\n"<<endl;
    cout<<"========================"<<endl;
    cout<<"         "<<day<<" "<<date<<endl;
    cout<<"========================"<<endl;
    //recursively display each event node in the LLL
    return display_all_events(event_list); 
}

bool calendar::display_all_events(event* curr)
{
    if(curr != nullptr)
    {
        curr->display();
        display_all_events(curr->getNext());
    }
    return true; 
}


bool calendar::add_existing_todo(event* curr)
{
    if(curr != nullptr)
    {
        if(curr->peek_todo() == 1)
        {
            curr->set_new();
            return true;
        }

        return add_existing_todo(curr->getNext());
    }
    //There is no To-Do in the list
    return false;
}


/* USER CLASS IMPLEMENTATION */
//this just provides another level of abstraction for the User
user::user(): user_name(nullptr){}

user::user(const user& src_user)
{
    this->user_name = new char[strlen(src_user.user_name)+1];
    strcpy(this->user_name, src_user.user_name);
}

user::~user()
{
    if(user_name)
        delete user_name;
    user_name = nullptr;
}


int user::main_program()
{
    bool check = true;
    char user_input;

    user_input = user_menu();
    while(user_input != 'x' && check == true)
    {
        execute(user_input);
        check = continue_menu();
        if(check == true)
        {
            user_input = user_menu();
        }
    }
    //clear any possible left overs
    this->remove_all_days();
    cout<<"*** PROGRAM EXIT ***"<<endl;
    return 0;
}


char user::user_menu()
{
    char user_input;

    cout<<"\n"<<endl;
    cout<<"------------- CS202 CALENDAR PROGRAM -------------"<<endl;
    cout<<"  Welcome, [user_name]. How can I help you today? "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"Manage the Calendar"<<endl;
    cout<<"1. Add a new day to the Calendar"<<endl;  //add_new_day()
    cout<<"2. Display days in the Calendar"<<endl;   //display_all_days()
    cout<<"3. Remove a day from the Calendar"<<endl;  //remove_day()
    cout<<"4. Remove all days from the Calendar"<<endl;   //remove_all_days()
    cout<<"\nManage the Events"<<endl;
    cout<<"a. Schedule a new event"<<endl;  //add_event()
    cout<<"b. Display all events"<<endl;   //display_events()
    cout<<"c. Remove an event"<<endl;    //remove_event()
    cout<<"d. Remove all events"<<endl;  //delete_all_events()
    cout<<"\nx. Exit Program\n"<<endl;

    cout<<"Please enter your selection: ";
    cin>>user_input;
    cin.ignore(1000, '\n');
    return user_input;
}


bool user::execute(char user_input)
{
   switch(user_input)
   {
       //Add a new day
       case '1':
           this->add_new_day();
           break;
           
       //Display all days
       case '2':  
           this->display_all_days();
           break;

       //remove one day
       case '3':
           this->remove_day();
           break;

       //remove all days
       case '4':
           this->remove_all_days();
           break;

       //add an event
       case 'a':
           this->add_event();
           break;

       //display all events
       case 'b':
           this->display_events();
           break;

       //remove one event
       case 'c':
           this->remove_event();
           break;

       //delete all events
       case 'd':
           this->delete_all_events();
           break;

       //exit the program
       case 'x':
           cout<<"exiting program..."<<endl;
           break;
       default:
           cout<<"[Invalid Input]"<<endl;
           break;
   }
   return true;
}


bool user::continue_menu()
{
    char yes_no;
    cout<<"Return to the Main Menu? (y/n): ";
    cin>>yes_no;

    if(yes_no == 'y' || yes_no == 'Y')
        return true;
    else
        return false;
}
