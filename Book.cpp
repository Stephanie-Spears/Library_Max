#include "Book.h"

Book::Book(void)
{
}

Book::Book(const string& title, const string& creator, const int size) : Item(title, creator, size)
{

}

Book::Book(const Item* in) : Item(in)
{
}

Book::~Book(void)
{
}
/*
ostream& operator<<(ostream& out, const Book* const book)
{
	out << static_cast<const Item*>(book);
	out << endl;
	book->printKeywords(out);
	out << endl << endl;
	return out;
}*/
ostream& Book::stream_write(ostream& out) const
{
	string title = this->getTitle();
	string creator = this->getCreator();
	int size = this->getSize();
	out << "-Book-" << endl;
	out << "author: " << '\t' << creator << endl;
	out << "# pages: " << '\t' << size << endl;
	out << "title: " << "\t\t" << title << endl;
	out << "keywords: " << '\t';
	this->printKeywords(out);
	out << endl << endl;
	return out;
}
