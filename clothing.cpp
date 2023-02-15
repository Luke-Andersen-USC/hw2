#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
    Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;
}
	
std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> keyWords;
	
	std::set<std::string> nameKeys = parseStringToWords(name_);
	std::set<std::string> brandKeys = parseStringToWords(brand_);

	for(set<std::string>::iterator it = nameKeys.begin(); it != nameKeys.end(); ++it)
	{
		keyWords.insert(*it);
	}
	
	for(set<std::string>::iterator it = brandKeys.begin(); it != brandKeys.end(); ++it)
	{
		keyWords.insert(*it);
	}
	
	keyWords.insert(size_);

	return keyWords;
}
	
std::string Clothing::displayString() const
{
	stringstream ss;
	ss << name_ << setw(10);
	ss << "\nSize: " << size_ << " Brand: " << brand_ << "\n"; 
	ss << fixed << setprecision(2) << price_ << " " << setw(3) << qty_ << " left.";
	return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << endl;
	os << name_ << endl;
	os << std::setprecision(2) << std::fixed << price_ << endl;
	os << qty_ << endl;
	os << size_ << endl;
	os << brand_ << endl;
}