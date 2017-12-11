#include "Library.h"
#include <iostream>
#include <cstdarg>




//CONSTRUCTOR
Library::Library() {}


//GENERAL

void Library::addKeywordsForItem(const Item* const item, int nKeywords, ...)
{
	// the code in this function demonstrates how to handle a vararg in C++

	va_list		keywords;
	char		*keyword;

	StringSet keywordSet;

	va_start(keywords, nKeywords);
	for (int i = 0; i < nKeywords; i++) {
		keyword = va_arg(keywords, char*);
		keywordSet.insert(keyword);
	}
	va_end(keywords);

	//make a verson of item that we can edit



	//TRY TO GET RID OF THIS
	Item* finder = (const_cast<Item*>(item));



	ItemSet::iterator it = booksByTitle.find(finder);
	if (it != booksByTitle.end())
	{
		booksByTitle.erase(*it);
		finder->setKeywords(keywordSet);
		Item *book = new Book(finder);
		booksByTitle.insert(book);
//		delete book;
	}

	it = albumsByTitle.find(finder);
	if (it != albumsByTitle.end())
	{
		albumsByTitle.erase(*it);
		finder->setKeywords(keywordSet);
		Item *album = new MusicAlbum(finder);
		albumsByTitle.insert(album);
//		delete album;
	}

	it = moviesByTitle.find(finder);
	if (it != moviesByTitle.end())
	{
		moviesByTitle.erase(*it);
		finder->setKeywords(keywordSet);
		Item *movie = new Movie(finder);
		moviesByTitle.insert(movie);
//		delete movie;
	}



	//start at the first keyword in list
	StringSet::iterator it2 = keywordSet.begin();
	while (it2 != keywordSet.end())
	{
		//make a new ItemSet
		ItemSet* iSet;
		//iset is now the list at iterator's keyword
		if (keywordMap.find(*it2) != keywordMap.end())
		{
			iSet = keywordMap.at(*it2);
		}
		else
		{
			iSet = new ItemSet;
		}
		//add copy to itemset
		iSet->insert(finder);
		//overwrite 
		keywordMap[*it2] = iSet;
//		delete iSet;
		it2++;
	}
}

const ItemSet* Library::itemsForKeyword(const string& keyword) const
{
	if (keywordMap.find(keyword) == keywordMap.end())
	{
		return NULL;
	}
	ItemSet* iSet = keywordMap.at(keyword);
	return iSet;
}



//BOOKS

const Item* Library::addBook(const string& title, const string& author, const int nPages)
{
	Item *book = new Book(title, author, nPages);

	booksByTitle.insert(book);

	ItemSet * authorSet;

	//if there are any books by this author
	if (booksByCreator.find(author) != booksByCreator.end())
	{
		authorSet = booksByCreator.at(author);
	}
	else
	{
		authorSet = new ItemSet;
	}

	authorSet->insert(book);

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

	//if there are any albums by this artist
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

	Item* finder = (const_cast<Item*>(musicAlbum));
	albumsByTitle.erase(finder);
	(static_cast<MusicAlbum*>(finder))->setMembers(memberSet);
	albumsByTitle.insert(finder);


	StringSet::iterator it = memberSet.begin();
	while (it != memberSet.end())
	{
		ItemSet* iSet;
		if (albumsByMember.find(*it) != albumsByMember.end())
		{
			iSet = albumsByMember.at(*it);

		}
		else
		{
			iSet = new ItemSet;
		}

		iSet->insert(finder);
		albumsByMember[*it] = iSet;
//		delete iSet;
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

	//if there are any movies by this director
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
//		delete iSet;
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


//DESTRUCTOR

void Library::deleteItemSetContents(ItemSet& itemSet)
{
	ItemSet::iterator it = itemSet.begin();

	Item * ptr;

	while(it != itemSet.end())
	{
		ptr = it->getPtr();
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
















/*
void Library::deleteItemSetContents(ItemSet& itemSet)
{
	ItemSet::iterator it = itemSet.begin();

	while(it != itemSet.end())
	{
		delete[] &it;
		it++;
	}

	itemSet.clear();
}

void Library::deleteMapContents(StringToItemSetMap& s2ism)
{
	StringToItemSetMap::iterator it = s2ism.begin();
	while (it != s2ism.end())
	{
		deleteItemSetContents(*it->second);
		delete[] &it->second;
		it++;
	}

}

*/
Library::~Library()
{
	deleteMapContents(keywordMap);
	deleteMapContents(booksByCreator);
	deleteMapContents(albumsByCreator);
	deleteMapContents(albumsByMember);
	deleteMapContents(moviesByCreator);
	deleteMapContents(moviesByMember);

	deleteItemSetContents(booksByTitle);
	deleteItemSetContents(albumsByTitle);
	deleteItemSetContents(moviesByTitle);
}


