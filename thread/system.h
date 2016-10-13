// system.h 
//	All global variables used in Nachos are defined here.
//

#ifndef SYSTEM_H
#define SYSTEM_H


#include "utility.h"
#include "thread.h"
#include "scheduler.h"
#include "interrupt.h"
#include "stats.h"
#include "timer.h"
#include "../userprog/bitmap.h"
#include "../userprog/page_manager.h"
#include "../userprog/swap.h"
#include "../userprog/inverted_translation_entry.h"

#include <map>

// Initialization and cleanup routines
extern void Initialize(int argc, char **argv); 	// Initialization,
						// called before anything else
extern void Cleanup();				// Cleanup, called when
						// Nachos is done.

extern Thread *currentThread;			// the thread holding the CPU
extern Thread *threadToBeDestroyed;  		// the thread that just finished
extern Scheduler *scheduler;			// the ready list
extern Interrupt *interrupt;			// interrupt status
extern Statistics *stats;			// performance metrics
extern Timer *timer;				// the hardware alarm clock

class AddrSpace;
extern Lock* processTableLock;
extern std::map<AddrSpace*, uint32_t> processThreadTable;

#define NUM_SYSTEM_LOCKS 10000
struct KernelLock {
  Lock* lock;
  AddrSpace* addrSpace;
  bool toBeDeleted;
  uint32_t threadsUsing;
  char* name;
};
extern Lock* lockTableLock;
extern KernelLock* lockTable[NUM_SYSTEM_LOCKS];

class Condition;
#define NUM_SYSTEM_CONDITIONS 10000
struct KernelCondition {
  Condition* condition;
  AddrSpace* addrSpace;
  bool toBeDeleted;
  uint32_t threadsUsing;
  char* name;
};
extern Lock* conditionTableLock;
extern KernelCondition* conditionTable[NUM_SYSTEM_CONDITIONS];

extern Lock* iptLock;
extern InvertedTranslationEntry ipt[NumPhysPages];
enum EvictionPolicy {
  FIFO = 0,
  RAND,
  NUM_EVICTION_POLICIES
};
extern EvictionPolicy evictionPolicy;
extern Lock* swapLock;
extern Swap* swapFile;

#ifdef USER_PROGRAM
#include "machine.h"
extern Machine* machine;  // user program memory and registers
extern PageManager* page_manager;
extern int currentTlb;
#endif

#ifdef FILESYS_NEEDED 		// FILESYS or FILESYS_STUB 
#include "filesys.h"
extern FileSystem  *fileSystem;
#endif

#ifdef FILESYS
#include "synchdisk.h"
extern SynchDisk   *synchDisk;
#endif

#ifdef NETWORK
#include "post.h"
extern PostOffice* postOffice;
#define MAX_MONITOR 1000
#define NUM_MONITORS 10000
#define NUM_MAILBOXES 10
extern int machineId;
extern int numServers;
extern Lock* mailboxesLock;
extern BitMap* mailboxes;
#endif
#endif // SYSTEM_H
