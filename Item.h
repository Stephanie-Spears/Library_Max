#pragma once

#include <ostream>
#include <set>
#include <string>

using namespace std;

class Item
{
public:
	Item(const string& title, const string& creator, const int size);
	Item();
	Item(const Item* in);
	virtual ~Item();

	//SETTERS
	void setCreator(const string& creator);
	void setTitle(const string& title);
	void setSize(const int size);
	void setKeywords(const set<string> keywords);

	//GETTERS
	string getCreator() const;
	string getTitle() const;
	int getSize() const;
	set<string> getKeywords() const;

	friend ostream& operator<<(ostream& out, const Item* const item);
	void operator = (const Item &i);

private:
	string title;
	string creator;
	int size;
	set<string> keywords;

protected:
	const void printKeywords(ostream& out) const;
	virtual ostream& stream_write(ostream&) const;
};

// You can't store Item* in an ItemSet, because that would disable the automatic
// sorting that set does. Containers in the C++ STL are designed to store
// INSTANCES, not POINTERS to instances.
//
// Instead we store instances of ItemPtr in the ItemSet defined in Library.h.
// Each instance of ItemPtr contains a pointer to an instance of Item. In this way,
// the container can call operator< for ItemPtr (which can then call operator<
// for Item) to determine the order in which to store the items it's given.
//
// When you add a Book instance to an ItemSet, you can do things like this:
//
//		ItemSet		books;					// defined in Library.h
//		Item		*book = new Book(...);
//
//		books.insert(book);
//
// The STL's set class will internally generate an instance of ItemPtr
// which will contain the pointer to the instance of Book.

class ItemPtr
{
private:
	Item * ptr;

public:
	ItemPtr(Item *ptr) : ptr(ptr) { }
	Item* getPtr() const { return ptr; }
};

// compare two instances of Item
bool operator<(const Item& i1, const Item& i2);

// compare two instances of ItemPtr
bool operator<(const ItemPtr& ip1, const ItemPtr& ip2);
