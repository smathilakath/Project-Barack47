Passport Office Simulation challenge - Clear Tax - Author : Sumod Madhavan
==========================================================================

<p>You are in charge of managing / building a passport service office. The job of your office is to take passport applications by citizens, and issue them a new passport.</p>
For a passport to be issued, you have three independent steps that need to be taken:

* Document verification
You collect documents from the person, and verify each document. Make sure they are correct, properly attested, collect ID proofs, etc.
Typically, this will take around 5-15 minutes per person.
* Police Verification
You check the person’s previous record and ask questions if required.
This can be very quick (1-2 minutes if there is no record), or take upto 25-30 minutes in case there is a prior record. Around 5-10% of applicants have a prior record.
* Biometrics collection

You get the fingerprints, etc from the person. This step usually takes around 5-7 minutes.
Each of these steps needs the person applying for a passport to be physically present.
Your job is to ensure that the maximum number of people get served – you want to design the office to be as efficient as possible.

The rough layout of your office is:

- The applicant will enter your office, check-in at the reception and receive a token number. This is a sequential number for any given date.
- This intake occurs once every hour – a fixed number of people come in at the start of each hour, from 9-5.
- They will be taken to a waiting area. The waiting area will have three televisions showing the tokens being served currently, at each stage.
- When the user sees his token number in the TV for stage 1 (document verification), they will go to the document verification area and sit with an agent to get their documents verified.
- Once they are done, they go back to the waiting area and wait for their number to show up for stage 2 (police verification), and so on.
<p>Each stage (document verification, police verification, etc) will have a fixed number of agents working on only those tasks.</p>

**Question:**

Given this layout, you can choose multiple algorithms to streamline your process.

* Global First come, first serve – for any given stage, always give the next available slot to the person whose token number is the earliest.
* Stage-wise First come, first serve – give the next available slot to the person who has been waiting the most amount of time after exiting the previous stage.
* Random – randomly assign the next available slot to any person waiting for it.

<p>Given an input data containing: </p>
- Number of agents assigned for each stage
- The estimated time taken at each stage (mentioned above)
<p>
Figure out which which algorithm is the most efficient: Which algorithm results in

the most number of cases served on any particular date.
Also, find out which algorithm is the most fair to the end user: which results in the least waiting time for each applicant, at the max possible intake rate.

</p>

## Table of Contents

* [Prerequisite](#prerequisite)
* [First use instructions](#First use instructions)
* [Assumption](#assumption)
* [Design](#design)
* [Implementation](#Implementation)
* [Testing](#testing)
* [Final Thoughts](#thoughts)


## Prerequisite

In order to successfully run this sample app you need a few things:

1. [Nachos](http://homes.cs.washington.edu/~tom/nachos/)

![NACHOS] (images/nachos.png "Nachos")

[Nachos](http://homes.cs.washington.edu/~tom/nachos/) is instructional software for teaching undergraduate, and potentially
graduate, level operating systems courses.  The Nachos distribution
comes with: 

   an overview paper
   simple baseline code for a working operating system
   a simulator for a generic personal computer/workstation
   sample assignments
   a C++ primer (Nachos is written in an easy-to-learn subset of C++, 
     and the primer helps teach C programmers our subset)

The assignments illustrate and explore all areas of modern operating
systems, including threads and concurrency, multiprogramming, 
system calls, virtual memory, software-loaded TLB's, file systems, 
network protocols, remote procedure call, and distributed systems.

The most up to date version of nachos is linked to the file called, 
nachos.tar.Z.  On March 1, 1994, this version was nachos-3.2.tar.Z,
but it will be periodically updated as bugs are fixed and features added.
REMEMBER TO TURN BINARY MODE ON WHEN RETRIEVING .Z FILES.

To get started, you should:
  1. use ftp to fetch the nachos.tar.Z file (turning on binary mode first)
  2. uncompress nachos.tar.Z
  3. tar -xf nachos.tar
  4. lpr paper.ps  -- print out the paper describing nachos
  5. lpr doc/*.ps  -- print out the sample assignments
  6. cd code; make print -- print out the nachos source code
  7. cd code; edit Makefile.dep -- select host machine type 
  8. cd code; make all -- compile nachos source code
  9. cd c++example; lpr *.ps *.h *.cc -- print out C++ primer

![Boot Strap] (images/boot.png "boot strap")

## First use instructions

1. Each entity of the passport office is implemented as a separate user program. The passport simulation can be run by executing the entities as separate user program and managing the shared data on one or more servers.

2. Allow for multiple servers to handle client requests.  Clients are to randomly choose a server to send their request to.  Locks, Conditions, and Monitors will be stored on the server the first CREATE request was sent to.  On a client request if the entity is not found on that server, the server must send requests to each of the other servers to find the requested entity.

3. We have the option to either user Semaphores or a more primitive method such as Thread::Sleep in the implementation. The implementation should address issues such as the lock not holding and other possibilities that violate the rule of mutual exclusion. The implementation must enforce the concept that only the thread that acquired the lock may release the lock. We are to ignore the instructions that if a thread is to do something illegal, that we must terminate Nachos. Made sure that the code is commented, and test the code running the conditiontest1.cc.

4. We are to create a simulation of the Passport Office that utilizes different threads for all of the staff and customers in the simulation. The simulation includes the following people and resources:

* Customer
* Application Clerk
* Picture Clerk
* Passport Clerk
* Cashier
* Manager

Each one of these people is responsible for a distinct set of actions and interactions with one another. Likewise, we are to keep track of items such as sales, and the sales from each clerk. The particular actions that we are to test include:

* Customers always take the shortest line, but no 2 customers ever choose the same shortest line at the same time
* Managers only read one from one Clerk's total money received, at a time.
* Customers do not leave until they are given their passport by the Cashier. 
* The Cashier does not start on another customer until they know that the last Customer has left their area
* Clerks go on break when they have no one waiting in their line
* Managers get Clerks off their break when lines get too long
* Total sales never suffers from a race condition
* The behavior of Customers is proper when Police arrive. This is before, during, and after. 

The simulation is to support the following numbers of each type of person:

* Customers: up to 50
* Clerks and Cashier: between 1 and 5
* Manager: only 1
* Police Officers: 10
 
## Assumption

* Consider Global First come, first serve,Stage-wise First come, first serve,Random as A,B,C.
* The most number of cases served can be achieved only using probability of A,B,C with AUBUC or AUB Intersect C or all the combinations to form a effective algorithm.
* Focus is more on the 	the most number of cases served with fault taulerance.
* State of a lock applied is either Free or Busy
* Lock wait Q should be thread pointers
* Condition variables have no states, but they have 3 operations
	* Wait
	* Signal
	* Broadcast.
* Assume that if multiple clerks are on break, and multiple lines reach more than 3 customers waiting in line, the manager is to wake up one clerk at a time at an order chosen by us (can be *Random*).
* Assume that 5% of the time, the Passport Clerk will make a mistake with a customer and will not be able to process their application and the customer is to return to the back of the line.
* Instead of using a data structure such as a list or an array, we use a Boolean to denote if a customer's application has been accepted, denoted by the Boolean 'isAppAccepted'.
* In the scenario with a limited number of customers, the clerk going on break scenario may result in breakage. For instance, if there is only one customer and a clerk goes on break- the customer will be standing in line eternally as more than three customers are required to be in line for the manager to bring the clerk back from the break. We do not have to address this particular item of breakage, it is allowed by this assignment.
* Each interaction between two threads should have a different lock, we should not be holding onto a lock for a long time. It is assumed that we use different values of the 'rs' parameter to get context switches in different places.
* The Manager class is a thread like the rest of the personelle in the simulation. In order to create timer capacity, we should use the Thread->Yield().
* 20-50 customer threads allowed in the Big System test. For personal testing, we can use any number of customer threads.
* All clerks can be bribed, but the cashier cannot be bribed.
* Make a form of user input to be able to set the number of clerks prior to running the simulation.

## Design

#### A description of Classes added and Methods.

- The method 'void Lock:Acquire() is supposed to do the following: make the state of the lock busy, make the current thread thw owner of the lock, otherwise if the lock is busy, we should put the current thread on the lock's waiting queue. 
- The method 'void Lock:Release() is supposed to release the lock from a current thread holding onto it. First, we disable interrupts. If a thread that is not the owner of a lock tries to release the lock, we inform them that they cannot perform that action, restore interrupts, and return. If the thread is the owner of the lock and the lock Q is not empty, we remove the waiting thread from the queue, make it the lock owner, and tell the scheduler that the thread is ready to run. Otherwise, we simply make the lock available and unset the ownership (the ownership is simply a pointer, unset it).
- Condition Variables have three operations: wait, or put myself to sleep, signal or wake up 1 sleeping thread, and broadcast or wake up all the sleeping threads.
- The method void Condition:Wait(Lock* lock)disables interrupts, and checks whether a lock is null or not null. If it is, inform the user and restore interrupts. If it is not null but waiting locks are null, we set the waiting lock to be the current lock, if the waiting lock is null, inform the user and return, and if it is ok to ait, we release the lock, and put the current thread to sleep, and acquire the lock and restore interrupts.
- The method void Condition:Signal(Lock* lock) checks to make sure that the lock passed in is a waiting lock, and if it is, it will wake up the waiting thread, remove the thread from the wait Q, and put the thread into the Ready Q. If the wait Q is empty, the waiting lock will be null.
- The method void Condition:Broadcast(Lock* lock) will simply perform a while-loop checking the wait Q, and will perform the function signal on all the locks in the Q.


#### Class Client (aka Customer in Simulation) contains:
  - The following variables: the int money representing how much money the customer has and int ssn to represent the social security number(AAdhar ID/Voter Id) and customer identifier. The class contains two booleans to represent the stages of going through the passport office: pictureTaken to indicate whether the customer has successfully interacted with the Picture Clerk and received a photo, and applicationAccepted to denote whether or not the customer's application has been accepted after interacting with the Application clerk. There is an additional Boolean, bribed, that keeps track of whether the customer has currently bribed during this line, or not. The bribe boolean is reset with each line that the customer is in. The int selfIndex represents the customer's own position in the customer queue (making it easier for the clerk to call). 
  - The int currClerkIndex represents the current clerk who the customer is speaking to's index. 
  - The following methods: 
   - moveUpInLine(), which will allow a customer with greater than or equal to 700 RS to change their bribed variable to true for the following line that they are in, and result in a net loss of 600 RS for the customer, 
   - setAppAccepted()- a method allowing the bool applicationAccepted to be set, 
   - setPictureTaken()- a method allowing the bool pictureTaken to be set, and the bool methods isAppAccepted(), isPictureTaken(), and alreadyBribed() which returns the booleans set in the Client class. Getter and setter methods for the selfIndex int. A getter and setter for the int currClerkIndex.

#### Class Application Clerk
  - The following variables: the int clerkState which indicates the clerks state as follows: 
   * 0 available
   * 1 busy
   * 2 on break
  - The int **lineCount** representing the total number of customers in the clerk's line, and the int bribeCount, indicating the number of customers who have bribed the clerk waiting in line. 
  - The int selfIndex represents the clerk's own position in the application clerk queue (making it easier for the clerk to call). 
  - The int currClientIndex represents the current client who the clerk is speaking to's index. 
  
  The following methods: 
  - a getter and setter method for clerkState, denoted as getclerkState() and setclerkState(), 
  - The method addToLine() which increases lineCount by 1
  - The method addToBribeLine() which increases the bribeCount by 1
  - The method goToWork() which changes the clerk's state to 1 (busy), and the method goOneBreak() which changes the clerk's state to 2(busy).  
  - Getter and setter methods for the selfIndex int. A getter and setter for the int currClientIndex.

#### Class Picture Clerk
  - The following variables: the int clerkState which indicates the clerks state as follows:
   * 0 available
   * 1 busy
   * 2 on break
  - The int lineCount representing the total number of customers in the clerk's line, and the int bribeCount, indicating the number of customers who have bribed the clerk waiting in line. The int selfIndex represents the clerk's own position in the picture clerk queue (making it easier for the clerk to call). The int currClientIndex represents the current client who the clerk is speaking to's index. 
  - The following methods: a getter and setter method for clerkState, denoted as getclerkState() and setclerkState(), the method addToLine() which increases lineCount by 1, the method addToBribeLine() which increases the bribeCount by 1, the method goToWork() which changes the clerk's state to 1 (busy), and the method goOneBreak() which changes the clerk's state to 2(busy).  Getter and setter methods for the selfIndex int. A getter and setter for the int currClientIndex.
 
#### Class Passport Clerk
  - The following variables: the int clerkState which indicates the clerks state as follows:
   * 0 available
   * 1 busy
   * 2 on break
  - The int lineCount representing the total number of customers in the clerk's line, and the int bribeCount, indicating the number of customers who have bribed the clerk waiting in line. The int selfIndex represents the clerk's own position in the picture clerk queue (making it easier for the clerk to call). The int currClientIndex represents the current client who the clerk is speaking to's index. 
  - The following methods: a getter and setter method for clerkState, denoted as getclerkState() and setclerkState(), the method addToLine() which increases lineCount by 1, the method addToBribeLine() which increases the bribeCount by 1, the method goToWork() which changes the clerk's state to 1 (busy), and the method goOneBreak() which changes the clerk's state to 2(busy).  Getter and setter methods for the selfIndex int. A getter and setter for the int currClientIndex.

#### Class Cashier
  - The following variables: the int clerkState which indicates the clerks state as follows:
   * 0 available
   * 1 busy
   * 2 on break
  - The int lineCount representing the total number of customers in the clerk's line, and the int bribeCount, indicating the number of customers who have bribed the clerk waiting in line. The int selfIndex represents the clerk's own position in the picture clerk queue (making it easier for the clerk to call). The int currClientIndex represents the current client who the clerk is speaking to's index. 
  - The following methods: a getter and setter method for clerkState, denoted as getclerkState() and setclerkState(), the method addToLine() which increases lineCount by 1, the method addToBribeLine() which increases the bribeCount by 1, the method goToWork() which changes the clerk's state to 1 (busy), and the method goOneBreak() which changes the clerk's state to 2(busy).  Getter and setter methods for the selfIndex int. A getter and setter for the int currClientIndex.

#### Class Manager
  - The following variables: A vector *aClerks* keeping track of all of the application clerks, a vector *pClerks* keeping track of all the picture clerks, a vector *ppClerks* keeping track of all of the passport clerks, and a vector *cClerks* keeping track of all of the cashiers. An int *aMoney* keeping track of all of the application clerk's money, an int *pMoney* keeping track of all of the picture clerk's money, an int *ppMoney* keeping track of all the passport clerk's money, an int *cMoney* keeping track of all of the cashier's money, and an int called *totalMoney* which is a sum of all of the clerks' money.
  The following methods: A getter and setter method for all of the clerks' respective money totals(getaMoney(),setaMoney(int), getpMoney(),setpMoney(int), getppMoney(), setppMoney(int), get cMoney(), setcMoney(int), gettotalMoney(), and settotalMoney(int, int, int, int), and a wakeClerk(Clerk) method that will change the state of a clerk currently on break because there are greater than three people waiting in their line.
 
#### Class Police
   - The following variables: the int money representing how much money the police has and int ssn to represent the social security number and police identifier. The class contains two booleans to represent the stages of going through the passport office: pictureTaken to indicate whether the police has successfully interacted with the Picture Clerk and received a photo, and applicationAccepted to denote whether or not the police's application has been accepted after interacting with the Application clerk. There is an additional Boolean, bribed, that keeps track of whether the police has currently bribed during this line, or not. The bribe boolean is reset with each line that the police is in. 
  The following methods: moveUpInLine(), which will allow a police with greater than or equal to 700 RS to change their bribed variable to true for the following line that they are in, and result in a net loss of 600 RS for the police, setAppAccepted()- a method allowing the bool applicationAccepted to be set, setPictureTaken()- a method allowing the bool pictureTaken to be set, and the bool methods isAppAccepted(), isPictureTaken(), and alreadyBribed() which returns the booleans set in the police class.

Upon receiving the server request, if a server has the requested entity it sends a ‘YES’ back to the requesting server and executes the action to be done.  If the server does not have the entity, it sends a ‘NO’ back to the requesting server.  The requesting server keeps track of if a ‘YES’ response has been received and the number of ‘NO’ responses it has received.  Upon receiving a ‘YES’ server response the requesting server is done handling the request.  Upon receiving all ‘NO’ server responses the server will in the case of a CREATE request create the requested entity and in all other cases return an error message.

For the use of Condition variables, the request path is slightly different because of the possibility that the Lock used for that Condition was created by a different server than the one the Condition variable was created on. To solve this, three new types of messages were added in the case that the CV was found on a server but its lock wasn’t: WAIT_CV_LOCK, SIGNAL_CV_LOCK, and BROADCAST_CV_LOCK. When received by a server, they check and see if they own the lock in question. If they do, then they execute the action necessary for that specific request, and then return a ‘YES’ to the server who owns the CV. The server owning the CV will then, if necessary, send a response back to the client who had originally signalled or broadcasted, as well as performing the actions necessary to maintain the wait queue of the CV.


## Implementation

#### Files modified 

1. synch.h
2. synch.cc

lock and condition code.

* threadtest.cc: implementation code for Passport office and testing

#### Data structures 

- Struct ApplicationMonitor (in threadtest.cc) accepts numApplicationClerks and numCustomers as arguments and sets conditions and locks for the normal lines and bribe lines.
- Struct PictureMonitor (in threadtest.cc) accepts numPictureClerks and numCustomers as arguments and sets conditions and locks for the normal lines and bribe lines.
- Struct PassportMonitor (in threadtest.cc) accepts numPassportClerks and numCustomers as arguments and sets conditions and locks for the normal lines and bribe lines.
- Struct CashierMonitor (in threadtest.cc) accepts numCashiers and numCustomers as arguments and sets conditions and locks for the normal lines and bribe lines.
- Struct ManagerMonitor (in threadtest.cc) accepts numClerksOnBreak as arguments and sets conditions and locks for clerks on break.
- Class Client (in threadtest.cc) contains int money, int ssn, and the booleans applicationAccepted, pictureTaken, bribed, and missingReqs and the public getters and setters for these variables.
- Class ApplicationClerk (in threadtest.cc) contains int clerkState, int lineCount, int bribeLineCount, int clerkMoney, and int myLine and the getters and setters for these variables.
- Class PictureClerk (in threadtest.cc) contains int clerkState, int lineCount, int bribeLineCount, int clerkMoney, and int myLine and the getters and setters for these variables.
- Class PassportClerk (in threadtest.cc) contains int clerkState, int lineCount, int bribeLineCount, int clerkMoney, and int myLine and the getters and setters for these variables.
- Class Cashier (in threadtest.cc) contains int clerkState, int lineCount, int bribeLineCount, int clerkMoney, and int myLine and the getters and setters for these variables.
- Class Manager (in threadtest.cc) contains ints representing each clerk's money amount, and the total money and getters and setters for these variables.
- Class police (in threadtest.cc) contains int money, int ssn, and the booleans applicationAccepted, pictureTaken, bribed, and missingReqs and the public getters and setters for these variables.
#### Data structures modified
- Lock class (in synch.cc, synch.h) implemented constructor, destructor, and member functions.
- Condition class (in synch.cc, synch.h) implemented constructor, destructor, and member functions.

#### Functions

- int getSmallestLine() in threadtest.cc, goes through all of the clerks of a certain type and returns the smallest line for each type of a certain clerk.
- void giveSSN(int line, int ssn) in threadtest.cc pushes the ssn variable into the line that it belongs in the list of clientSSNs.
- void giveReqs(int line, int completed) in threadtest.cc pushes the int completed into the line that it belongs in the list of clientReqs.
- void giveCertifications(int line, bool certified) in threadtest.cc pushes the boolean certified into the line that it belongs in the list of customerCertifications.
- void joinApplicationLine() in threadtest.cc allows the client to get the AppMonitor lock and later to release it.
- void joinPictureLine() in threadtest.cc allows the client to get the PictureMonitor lock and later to release it.
- void joinPassportLine() in threadtest.cc allows the client to get the PassportMonitor lock and later to release it.
- void joinCashierLine() in threadtest.cc allows the client to get the CashierMonitor lock and later to release it.
- void createCustomer() in threadtest.cc sets a random money number, creates a new customer with a random money number, and adds the customer to the customers list.
- void createApplicationClerk() in threadtest.cc creates a new application clerk and pushes it to the application clerk list.
- void createPictureClerk() in threadtest.cc creates a new picture clerk and pushes it to the picture clerk list.
- void createPassportClerk() in threadtest.cc creates a new passport clerk and pushes it to the passport clerk list.
- void createCashier() in threadtest.cc creates a new cashier and pushes it to the cashiers list.
- void createManager() in threadtest.cc creates a single new manager.
- void createPolice() in threadtest.cc sets a random money number, creates a new police with a random money number, and adds the police to the police list.
- void problem2() in threadtest.cc initiates the menu for setting numbers for the number of customers, clerks, and police. It accepts customer inputs, and creates threads based on the number of customer inputs.
- Lock::Lock(char* debugName) in synch.cc is the lock constructor, it initializes the name, state (available), and the owner (null).
- Lock::~Lock() in synch.cc is the lock destructor.
- void Lock::Acquire() in synch.cc acquires the lock if possible and sets the owner thread to the current thread.
- void Lock::Release() in synch.cc releases the lock if possible, sets the owner thread to null, and sets the lock state to available.
- Condition::Condition(char* debugName) in synch.cc is the constructor and initializes the debugName, waitingLock, and queue.
- Condition::~Condition() in synch.cc is the condition destructor.
- void Condition::Wait(Lock* conditionLock) disables interrupts, waits for the condition, adds the current thread to the queue, releases the lock, puts the current thread to sleep, acquires the conditionLock, and then re-enables interrupts. 
- void Condition::Signal(Lock* conditionLock) signals for one thread to wake up, it disables interrupts, removes one thread from the queue and schedules it, sets the waiting lock to null, and then re-enables interrupts.
- void Condition::Broadcast(Lock* conditionLock) runs the Condition::Signal on all of the threads to wake them all up.

## Testing

- Run the following command:
- nachos-P2

**We will perform the following tests:**

1. You should be able to enter the number of clients and all different types of clerks and police in the command prompt and verify that the number you entered is the number that the simulation produced.
Test: Run the simulation and interract with the input. You can follow the instructions and choose the allowable values of each type of thread, or verify that error-capture is working correctly.
**Expected Output:**
View a menu that allows you to enter through command line the number of customers, clerks, and police.
2. Customers always take the shortest line, but no 2 customers ever choose the same shortest line at the same time
Test: Run the simulation and verify that the each customer you created is joining the shortest line. Now, create 2 customers and verify that they do not both join the same shortest line at the same time based on the output.
**Expected Output:**
Customer [identifier] has gotten in regular line for ApplicationClerk [identifier].
Customer [identifier] has gotten in regular line for PictureClerk [identifier].
Customer [identifier] has gotten in regular line for PassportClerk [identifier].
Customer [identifier] has gotten in regular line for Cashier [identifier].
3. Managers only read one from one Clerk's total money received, at a time.
Test: Run the simulation, and observe the nature of the output. Due to the way that the money system is coded, it is not possible for the managers to read from more than one clerk's total money received at a time.
**Expected Output:**
Manager has counted a total of RS[amount of money] for ApplicationClerks
Manager has counted a total of RS[amount of money] for PictureClerks
Manager has counted a total of RS[amount of money] for PassportClerks
Manager has counted a total of RS[amount of money] for Cashiers
4. Customers do not leave until they are given their passport by the Cashier. The Cashier does not start on another customer until they know that the last Customer has left their area.
Test:Create customers in the simulation, and verify that they have gone through each state prior to receiving a passport from the cashier. Once you view the message that the cashier has given the customer with the identifier their passport, watch for a message from the same customer that they are leaving the passport office. Only after that message is printed can the cashier become available for a new customer.
**Expected Output:**
Cashier [identifier] has provided Customer[identifier] their completed passport
Cashier [identifier] has provided Customer[identifier] their completed passport
Customer [identifier] is leaving the Passport Office.
Cashier [identifier] has signalled a Customer to come to their counter.
5. Clerks go on break when they have no one waiting in their line
Test: Create intentionally fewer customers, like 1-2. Watch the clerks who are currently not interacting with the customers to verify whether or not the clerks should go on break. 
**Expected Output:**
XXClerk [identifier] is going on break
6. Managers get Clerks off their break when lines get too long
Test: Verify that when a clerk is on break, if there are 3 or more people in the line, that the manager correctly identifies the clerk tied to the line and wakes the clerk from sleep.
**Expected Output:**
XXClerk [identifier] is going on break
Customer [identifier] has gotten in regular line for XXClerk [identifier]
Customer [identifier] has gotten in regular line for XXClerk [identifier]
Customer [identifier] has gotten in regular line for XXClerk [identifier]
Customer [identifier] has gotten in regular line for XXClerk [identifier]
Manager has woken up a XXClerk
XXClerk [identifier] is coming off break
7. Total sales never suffers from a race condition
Test: Run the simulation, verify that there are no race conditions. Due to the nature of the money system, there should not be.
Expected Output: N/A
8. The behavior of Customers is proper when police arrive. This is before, during, and after.
Test: Run the simulation, add a police. Verify that customers are acting normally prior to the police, that they leave the building when the police arrives, and when he leaves the customers return back to normal.
Expected Output (One of many possible examples):
Cashier [identifier] has signalled a Customer to come to their counter.
Customer [identifier] has given Cashier [identifier] RS100.
police [identifier] has gotten in regular line for ApplicationClerk [identifier].
Customer [identifier] is going outside the Passport Office because their is a police present.

**To test the distributed passport office simulation, run the following commands**

    '''Bash

    nachos -server -m 0 -sn 1
    nachos -m 1 -sn 1 -x mini_passport_office_net_test

    '''

***To test Condition Variables with multiple servers, run the following commands in multiple windows from the network directory:***

    '''Bash

    nachos -sn 2 -server -m 0
    nachos -sn 2 -server -m 1
    nachos -sn 2 -m 2 -x ../test/conditiontest1
    nachos -sn 2 -m 3 -x ../test/conditiontest2

    '''
This shows that waiting and signalling work as distributed RPCs. Setting the random seed differently will change where the Condition and Lock variables are initially created

## Final Thoughts

1. You should be able to enter the number of clients and all different types of clerks and police in the command prompt (within acceptable range) and verify that the number you entered is the number that the simulation produced.
2. Customers always take the shortest line, but no 2 customers ever choose the same shortest line at the same time
3. Managers only read one from one Clerk's total money received, at a time.
4. Customers do not leave until they are given their passport by the Cashier. The Cashier does not start on another customer until they know that the last Customer has left their area
5. Clerks go on break when they have no one waiting in their line
6. Managers get Clerks off their break when lines get too long
7. Total sales never suffers from a race condition
8. The behavior of Customers is proper when police arrive. This is before, during, and after.
9. The passport office simulation should complete successfully (all customers should leave).
10.The manager thread should remain running and periodically output the collected money for the office.


## Reporting Issues ###

Report issues in the issue section.