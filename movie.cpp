#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
    Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating;
}
	
std::set<std::string> Movie::keywords() const
{
	std::set<std::string> keyWords;
	
	std::set<std::string> nameKeys = parseStringToWords(name_);
	std::set<std::string> genreKeys = parseStringToWords(genre_);

	for(set<std::string>::iterator it = nameKeys.begin(); it != nameKeys.end(); ++it)
	{
		keyWords.insert(*it);
	}
	
	for(set<std::string>::iterator it = genreKeys.begin(); it != genreKeys.end(); ++it)
	{
		keyWords.insert(*it);
	}
	
	keyWords.insert(rating_);

	return keyWords;
}
	
std::string Movie::displayString() const
{
	stringstream ss;
	ss << name_ << setw(10);
	ss << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n"; 
	ss << fixed << setprecision(2) << price_ << " " << setw(3) << qty_ << " left.";
	return ss.str();
}

void Movie::dump(std::ostream& os) const
{
	os << std::setprecision(2) << std::fixed;
	os << category_ << endl;
	os << name_ << endl;
	os << price_ << endl;
	os << std::setprecision(2) << std::fixed << qty_ << endl;
	os << genre_ << endl;
	os << rating_ << endl;
}
