#pragma once

#include "Item.h"

class Movie :
	public Item
{
public:
	Movie(void);
	Movie(const string& title, const string& creator, const int size);
	Movie(const Item* in);
	~Movie(void);

	void setCast(const set<string> castSet);

private:
	set<string> cast;
	void printCast(ostream& out) const;
protected:
	virtual ostream& stream_write(ostream&) const;
};
