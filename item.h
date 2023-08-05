#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>
#include <time.h>  // Used by timing functions

#include <iostream>
using namespace std;

static int maxKey = -10;

class Item {
private:
	string process_name;
	int burst_cpu;
	int priority;
public:
	Item(string t = "", int c = 0, int p = maxKey) { process_name = t; burst_cpu = c; priority = p; }
	// The following is for those times when we actually
	//   need to get a value, rather than compare objects.
	int null()
	{
		return priority == maxKey;
	}
	string get_process_name()  const { return process_name; }
	int get_burst_cpu()  const { return burst_cpu; }
	int get_priority() const { return priority; }
	void set_new_burst(int new_burst) { burst_cpu = new_burst; }
};
 
// Let us print out Items easily
inline ostream& operator<<(ostream& s, const Item& i)
{
	return s << i.get_process_name() << " " << i.get_burst_cpu() << " " << i.get_priority() << endl;
}
#endif