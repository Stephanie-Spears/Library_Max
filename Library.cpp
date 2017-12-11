#include "Library.h"
#include <iostream>
#include <cstdarg>




//CONSTRUCTOR
Library::Library() {}


//GENERAL

void Library::addKeywordsForItem(const Item* const item, int nKeywords, ...)
{
	va_list		keywords;
	char		*keyword;

	StringSet keywordSet;

	va_start(keywords, nKeywords);
	for (int i = 0; i < nKeywords; i++) {
		keyword = va_arg(keywords, char*);
		keywordSet.insert(keyword);
	}
	va_end(keywords);

	//this isn't ideal but I couldn't think up another way
	Item* finder = (const_cast<Item*>(item));

	//if finder is a book
	ItemSet::iterator it = booksByTitle.find(finder);
	if (it != booksByTitle.end())
	{
		booksByTitle.erase(*it);
		finder->setKeywords(keywordSet);
		booksByTitle.insert(finder);
	}
	//if finder is an album
	it = albumsByTitle.find(finder);
	if (it != albumsByTitle.end())
	{
		albumsByTitle.erase(*it);
		finder->setKeywords(keywordSet);
		albumsByTitle.insert(finder);
	}
	//if finder is a movie
	it = moviesByTitle.find(finder);
	if (it != moviesByTitle.end())
	{
		moviesByTitle.erase(*it);
		finder->setKeywords(keywordSet);
		moviesByTitle.insert(finder);
	}

	//start at the first keyword in list
	StringSet::iterator it2 = keywordSet.begin();
	while (it2 != keywordSet.end())
	{
		ItemSet* iSet;
		//iset is now the list at iterator's keyword
		if (keywordMap.find(*it2) != keywordMap.end())
		{
			iSet = keywordMap.at(*it2);
		}
		//or, if there was no list at that keyword, we create one.
		else
		{
			iSet = new ItemSet;
		}
		//add copy to itemset
		iSet->insert(finder);
		//overwrite, note this works even when our if statement failed, 
		//since the [] operator creates a place in our map if its argument isn't found
		keywordMap[*it2] = iSet;
		it2++;
	}
}

const ItemSet* Library::itemsForKeyword(const string& keyword) const
{
	if (keywordMap.find(keyword) == keywordMap.end())
	{
		return NULL;
	}
	//returns the set of items labelled with this keyword
	ItemSet* iSet = keywordMap.at(keyword);
	return iSet;
}



//BOOKS

const Item* Library::addBook(const string& title, const string& author, const int nPages)
{
	//create a new book object and insert it to our itemSet
	Item *book = new Book(title, author, nPages);
	booksByTitle.insert(book);

	//a pointer to a set of books written by this specific author
	ItemSet * authorSet;

	//if there are any books by this author, grab the set of them
	if (booksByCreator.find(author) != booksByCreator.end())
	{
		authorSet = booksByCreator.at(author);
	}
	else
	//if not, create a new set
	{
		authorSet = new ItemSet;
	}

	//add this specific book to the set of books by this author
	authorSet->insert(book);

	//add (or overwrite) the set of books to the map, with the key being the author's name.
	booksByCreator[author] = authorSet;

	return book;
}

const ItemSet* Library::booksByAuthor(const string& author) const
{
	if (booksByCreator.find(author) == booksByCreator.end())
	{
		return NULL;
	}
	ItemSet* iSet = booksByCreator.at(author);
	return iSet;
}

const ItemSet* Library::books() const
{
	const ItemSet* books = &booksByTitle;
	return books;
}



//ALBUMS

const Item* Library::addMusicAlbum(const string& title, const string& band, const int nSongs)
{
	Item *album = new MusicAlbum(title, band, nSongs);
	
	albumsByTitle.insert(album);

	ItemSet * bandSet;

	if (albumsByCreator.find(band) != albumsByCreator.end())
	{
		bandSet = albumsByCreator.at(band);
	}
	else
	{
		bandSet = new ItemSet;
	}

	bandSet->insert(album);

	albumsByCreator[band] = bandSet;

	return album;
}

void Library::addBandMembers(const Item* const musicAlbum, const int nBandMembers, ...)
{
	va_list members;
	char *member;


	StringSet memberSet;
	va_start(members, nBandMembers);
	for (int i = 0; i < nBandMembers; i++) {
		member = va_arg(members, char*);
		memberSet.insert(member);
	}
	va_end(members);


	//again, i dont think const casting is ideal. 

	Item* finder = (const_cast<Item*>(musicAlbum));
	//we erase the old entry of this album (the one containing no data on band members)
	albumsByTitle.erase(finder);
	//cast finder into an album, so we can invoke setMembers function
	(static_cast<MusicAlbum*>(finder))->setMembers(memberSet);
	//add the modified album back to the set
	albumsByTitle.insert(finder);

	StringSet::iterator it = memberSet.begin();
	while (it != memberSet.end())
	{
		ItemSet* iSet;
		//grab the set of albums by this musician
		if (albumsByMember.find(*it) != albumsByMember.end())
		{
			iSet = albumsByMember.at(*it);

		}
		//....or create it if it doesn't already exist
		else
		{
			iSet = new ItemSet;
		}
		//add this album to the set
		iSet->insert(finder);
		//overwrite the previous version of the set (or create a new entry in the map)
		albumsByMember[*it] = iSet;
		it++;
	}

}

const ItemSet* Library::musicByBand(const string& band) const
{
	if (albumsByCreator.find(band) == albumsByCreator.end())
	{
		return NULL;
	}
	ItemSet* iSet = albumsByCreator.at(band);
	return iSet;
}


const ItemSet* Library::musicByMusician(const string& musician) const
{
	if (albumsByMember.find(musician) == albumsByMember.end())
	{
		return NULL;
	}
	ItemSet* iSet = albumsByMember.at(musician);
	return iSet;
}

const ItemSet* Library::musicAlbums() const
{
	const ItemSet* albums = &albumsByTitle;
	return albums;
}



//MOVIES

const Item* Library::addMovie(const string& title, const string& director, const int nScenes)
{
	Item *movie = new Movie(title, director, nScenes);

	moviesByTitle.insert(movie);

	ItemSet * directorSet;

	if (moviesByCreator.find(director) != moviesByCreator.end())
	{
		directorSet = moviesByCreator.at(director);
	}
	else
	{
		directorSet = new ItemSet;
	}

	directorSet->insert(movie);

	moviesByCreator[director] = directorSet;

	return movie;
}

void Library::addCastMembers(const Item* const movie, const int nCastMembers, ...)
{
	va_list members;
	char *member;

	StringSet memberSet;

	va_start(members, nCastMembers);
	for (int i = 0; i < nCastMembers; i++) {
		member = va_arg(members, char*);
		memberSet.insert(member);
	}
	va_end(members);

	Item* finder = (const_cast<Item*>(movie));
	moviesByTitle.erase(finder);
	(static_cast<Movie*>(finder))->setCast(memberSet);
	moviesByTitle.insert(finder);

	StringSet::iterator it = memberSet.begin();
	while (it != memberSet.end())
	{
		ItemSet*iSet;
		if (moviesByMember.find(*it) != moviesByMember.end())
		{
			iSet = moviesByMember.at(*it);
		}
		else
		{
			iSet = new ItemSet;
		}

		iSet->insert(finder);
		moviesByMember[*it] = iSet;
		it++;
	}
}

const ItemSet* Library::moviesByDirector(const string& director) const
{
	if (moviesByCreator.find(director) == moviesByCreator.end())
	{
		return NULL;
	}
	ItemSet* iSet = moviesByCreator.at(director);
	return iSet;
}

const ItemSet* Library::moviesByActor(const string& actor) const
{
	if (moviesByMember.find(actor) == moviesByMember.end())
	{
		return NULL;
	}
	ItemSet* iSet = moviesByMember.at(actor);
	return iSet;
}

const ItemSet* Library::movies() const
{
	const ItemSet* movies = &moviesByTitle;
	return movies;
}



//DESTRUCTOR FUNCS

void Library::deleteItemSetContents(ItemSet& itemSet)
{
	ItemSet::iterator it = itemSet.begin();

	Item * ptr;

	while(it != itemSet.end())
	{
		ptr = it->getPtr();
		delete ptr;
		it++;
	}

}

void Library::deleteMapContents(StringToItemSetMap& s2ism)
{
	StringToItemSetMap::iterator it = s2ism.begin();
	ItemSet * setPtr;

	while(it != s2ism.end())
	{
		setPtr = it->second;
		delete setPtr;
		it++;
	}
}

Library::~Library()
{
	deleteItemSetContents(booksByTitle);
	deleteItemSetContents(albumsByTitle);
	deleteItemSetContents(moviesByTitle);

	deleteMapContents(keywordMap);
	deleteMapContents(booksByCreator);
	deleteMapContents(albumsByCreator);
	deleteMapContents(albumsByMember);
	deleteMapContents(moviesByCreator);
	deleteMapContents(moviesByMember);
}


