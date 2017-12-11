#pragma once

#include "Item.h"

class MusicAlbum :
	public Item
{
public:
	MusicAlbum(void);
	MusicAlbum(const string& title, const string& creator, const int size);
	MusicAlbum(const Item* in);
	~MusicAlbum(void);

	void setMembers(const set<string> memberSet);

//	friend ostream& operator<<(ostream& out, const MusicAlbum* const album);
private:
	set<string> members;
	void printMembers(ostream& out) const;
protected:
	virtual ostream& stream_write(ostream&) const;

};

//ostream& operator<<(ostream& out, const MusicAlbum* const album);
