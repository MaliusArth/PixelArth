/*
 * Example of using reference counting in C++.
 *
 * Author: Damian Pietras
 *
 * This source code is public domain.
 *
 * http://www.linuxprogrammingblog.com/
 */

#ifndef REFERENCETOOBJ_H_
#define REFERENCETOOBJ_H_

template< class T >
class ReferenceToObj
{
	T *obj;

	void decRef () throw ()
	{
		if (obj && obj->decRefCount() == 0) {
			delete obj;
			obj = 0;
		}
	}

public:
	class NullDereference
	{
	};

	ReferenceToObj (T *obj = 0) throw () :
		obj (obj)
	{
	}

	ReferenceToObj (ReferenceToObj< T > &orig)
	{
		obj = orig.obj;
		if (obj)
			obj->incRefCount ();
	}

	T &operator* () throw (NullDereference)
	{
		if (!obj)
			throw NullDereference ();
		return *obj;
	}

	T *operator-> () throw (NullDereference)
	{
		if (!obj)
			throw NullDereference ();
		return obj;
	}

	bool operator== (const ReferenceToObj< T >&right)
	{
		return obj == right.obj;
	}

	ReferenceToObj< T > &operator= (ReferenceToObj< T > &right)
	{
		if (this == &right)
			return *this;

		if (right.obj)
			right.obj->incRefCount ();

		decRef ();

		obj = right.obj;

		return *this;
	}

	operator bool ()
	{
		return obj != 0;
	}

	~ReferenceToObj< T > ()
	{
		decRef ();
	}
};

#endif
