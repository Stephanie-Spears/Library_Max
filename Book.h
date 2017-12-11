#pragma once

#include "Item.h"

class Book :
	public Item
{
public:
	Book(void);
	Book(const string& title, const string& creator, const int size);
	Book(const Item* in);
	~Book(void);
//	friend		ostream& operator<<(ostream& out, const Book* const book);

protected:
	virtual ostream& stream_write(ostream&) const;
};

