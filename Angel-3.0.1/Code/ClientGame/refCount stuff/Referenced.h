/*
 * Example of using reference counting in C++.
 *
 * Author: Damian Pietras
 *
 * This source code is public domain.
 *
 * http://www.linuxprogrammingblog.com/
 */

#ifndef REFERENCED_H_
#define REFERENCED_H_

class Referenced
{
	int refCount;

public:
	Referenced () throw () :
		refCount (1)
	{
	}

	void incRefCount () throw ()
	{
		refCount++;
	}

	int decRefCount () throw ()
	{
		return --refCount;
	}
};

#endif
