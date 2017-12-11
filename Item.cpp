#include "Item.h"

Item::Item(const string& title, const string& creator, const int size)
{
	this->title = title;
	this->creator = creator;
	this->size = size;
}

Item::Item()
{
	this->title = "EMPTY_TITLE";
	this->creator = "EMPTY_CREATOR";
	this->size = -1;
}

Item::Item(const Item* in)
{
	this->title = in->getTitle();
	this->creator = in->getCreator();
	this->size = in->getSize();
	this->keywords = in->getKeywords();
}

void Item::operator = (const Item &i)
{
	title = i.title;
	creator = i.creator;
	size = i.size;
	keywords = i.keywords;
}


Item::~Item()
{

}

//SETTERS
void Item::setCreator(const string& creator)
{
	this->creator = creator;
}

void Item::setTitle(const string& title)
{
	this->title = title;
}

void Item::setSize(const int size)
{
	this->size = size;
}

void Item::setKeywords(const set<string> keywords)
{
	this->keywords = keywords;
}

//GETTERS
string Item::getCreator() const
{
	return this->creator;
}

string Item::getTitle() const
{
	string outtitle = title;
	return outtitle;
}

int Item::getSize() const
{
	return this->size;
}

set<string> Item::getKeywords() const
{
	return this->keywords;
}

const void Item::printKeywords(ostream& out) const
{
	set<string>::iterator it = this->keywords.begin();
	while (it != this->keywords.end())
	{
		out << *it << ", ";
		it++;
	}
}

//OVERLOADS
bool operator<(const Item& i1, const Item& i2)
{
	const string n1 = i1.getTitle();
	const string n2 = i2.getTitle();

	bool value = (n1 < n2);
	return value;
}

bool operator<(const ItemPtr& ip1, const ItemPtr& ip2)
{
	Item* i1 = ip1.getPtr();
	Item* i2 = ip2.getPtr();

	const string n1 = i1->getTitle();
	const string n2 = i2->getTitle();

	bool value = (n1 < n2);
	return value;
}

ostream& Item::stream_write(ostream& out) const
{
	out << "not this one !";
	return out;
}

ostream& operator<<(ostream& out, const Item* const item)
{
	return item->stream_write(out);
}

/*
ostream& operator<<(ostream& out, const Item* const item)
{
	const string title = item->getTitle();
	const string creator = item->getCreator();
	const int size = item->getSize();


	out << title << endl;
	out << creator << endl;
	out << size << endl;

	return out;
}
*/
