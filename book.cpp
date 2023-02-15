#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"


using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn) :
    Product(category, name, price, qty)
{
	author_ = author;
	isbn_ = isbn;
}
	
std::set<std::string> Book::keywords() const
{
	std::set<std::string> keyWords;
	
	std::set<std::string> nameKeys = parseStringToWords(name_);
	std::set<std::string> authorKeys = parseStringToWords(author_);

	for(set<std::string>::iterator it = nameKeys.begin(); it != nameKeys.end(); ++it)
	{
		keyWords.insert(*it);
	}
	
	for(set<std::string>::iterator it = authorKeys.begin(); it != authorKeys.end(); ++it)
	{
		keyWords.insert(*it);
	}

	keyWords.insert(isbn_);

	return keyWords;
}


	
std::string Book::displayString() const
{
	stringstream ss;
	ss << name_ << setw(10);
	ss << "\nAuthor: " << author_ << " ISBN: " << isbn_ << "\n"; 
	ss << fixed << setprecision(2) << price_ << " " << setw(3) << qty_ << " left.";
	return ss.str();
}

void Book::dump(std::ostream& os) const
{
	os << category_ << endl;
	os << name_ << endl;
	os << price_ << endl;
	os << fixed << setprecision(2) << qty_ << endl;
	os << isbn_ << endl;
	os << author_ << endl;
}