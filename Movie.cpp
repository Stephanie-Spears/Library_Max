#include "Movie.h"

Movie::Movie(void)
{
}

Movie::Movie(const string& title, const string& creator, const int size) : Item(title, creator, size)
{
}

Movie::Movie(const Item* in) : Item(in)
{
}

Movie::~Movie(void)
{
}

void Movie::setCast(const set<string> castSet)
{
	this->cast = castSet;
}

void Movie::printCast(ostream& out) const
{
	set<string>::iterator it = this->cast.begin();
	while (it != this->cast.end())
	{
		out << *it;
		it++;
		if(it != this->cast.end())
		{
			out << ", ";
		}
	}
}

ostream& Movie::stream_write(ostream& out) const
{
	string title = this->getTitle();
	string creator = this->getCreator();
	int size = this->getSize();	
	out << "-Movie-" << endl;
	out << "director: " << '\t' << creator << endl;
	out << "# scenes: " << '\t' << size << endl;
	out << "cast: " << "\t\t";
	this->printCast(out);
	out << endl;
	out << "title: " << "\t\t" << title << endl;
	out << "keywords: " << '\t';
	this->printKeywords(out);
	out << endl << endl;
	return out;
}

