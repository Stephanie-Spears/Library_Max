#include "MusicAlbum.h"

MusicAlbum::MusicAlbum(void)
{
}

MusicAlbum::MusicAlbum(const string& title, const string& creator, const int size) : Item(title, creator, size)
{
}

MusicAlbum::MusicAlbum(const Item* in) : Item(in)
{
}

MusicAlbum::~MusicAlbum(void)
{
}

void MusicAlbum::setMembers(const set<string> memberSet)
{
	this->members = memberSet;
}

void MusicAlbum::printMembers(ostream& out) const
{
	set<string>::iterator it = this->members.begin();
	while (it != this->members.end())
	{
		out << *it;
		it++;
		if(it != this->members.end())
		{
			out << ", ";
		}
	}
}

ostream& MusicAlbum::stream_write(ostream& out) const
{
	string title = this->getTitle();
	string creator = this->getCreator();
	int size = this->getSize();
	out << "-Music Album-" << endl;
	out << "band: " << "\t\t" << creator << endl;
	out << "# songs: " << '\t' << size << endl;
	out << "members: " << '\t';
	this->printMembers(out);
	out << endl;
	out << "title: " << "\t\t" << title << endl;
	out << "keywords: " << '\t';
	this->printKeywords(out);
	out << endl << endl;
	return out;
}
