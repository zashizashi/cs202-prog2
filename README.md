# cs202-prog2

Program #2 – Building a Hierarchy using Dynamic Binding
For your second program, you will be creating a C++ OOP solution to support at least three different pieces of information that you keep on a calendar. Create a base class for the general calendar item that is common among the three classes. The data and functions that are common should be pushed up, and the differences derived.
Then, create three different derived classes for specific types of items that you like to schedule (you can use some of the examples I have provided or create your own).
1. It is important that each type of calendar item have similarities in functionality (but differences in the data that they need).
2. One calendar item should have a list of items (such as a todo list, a list to remember, a list of goals, etc.)
**You need 3 member functions in each of the three forms of calendar item in addition to your constructors and destructors **; with dynamic binding, these need to be self similar in nature. For at least one of your derived classes, plan to have a different function that is not self similar so that you can experience RTTI in practice; this is a requirement.
The purpose of this assignment is to use and experience dynamic binding. The requirement for this application is to have at least three DIFFERENT types of classes, derived from a common base class! To use dynamic binding, there needs to be a self-similar interface among the derived class methods but the implementation of the methods would need to be different in some way for you to make the most of this experience.

Program #2 – Data Structure Requirements
The real beauty of dynamic binding is that we can have a data structure be a collection of different data types! There needs to be ONE data structure of base class pointers used to represent your weekly calendar. This data structure will keep track of all of the different items that are scheduled for the week, using upcasting. Luckily, with upcasting, a base class pointer can point to any object within the hierarchy.
The data structure will be a doubly linked list of calendar days, where each day has a Linear linked list of base class pointers. Implementation of the data structure(s) requires full support of insert, removal, display, retrieval, and remove-all.
ALL repetitive data structure algorithms should be implemented recursively

Program #2 – Important C++ Syntax
Remember to support the following constructs as necessary:
1. Every class should have a default constructor
2. Every class that manages dynamic memory must have a destructor
3. Every class that manages dynamic memory must have a copy constructor
4. If a derived class has a copy constructor, then it MUST have an initialization list to cause the base class copy constructor to be invoked
5. Make sure to specify the base class’ destructor as virtual (but don’t make it a pure virtual function)
6. It is expected that you will experience RTTI with dynamic_cast in this assignment
