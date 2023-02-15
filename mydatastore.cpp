#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::~MyDataStore() { 

	for(vector<Product*>::iterator it = stock.begin(); it != stock.end(); it++)
	{
		delete *it;
	}
	for(map<std::string,User*>::iterator it = usernameMap.begin(); it != usernameMap.end(); it++)
	{
		delete it->second;
	}
}

void MyDataStore::addProduct(Product* p)
{
	stock.push_back(p);

	std::set<std::string> keys = p->keywords();

	for(std::set<std::string>::iterator it = keys.begin(); it != keys.end(); it++)
	{

		//add new key to key map
		if(keyMap.find(convToLower(*it)) == keyMap.end())
		{
			//da fuq to do here (how to put new vector into map)
			std::set<Product*> products;
			keyMap[convToLower(*it)] = products;
		}
		//add product to product set
		keyMap[convToLower(*it)].insert(p);
		
	}
}

void MyDataStore::addUser(User* u)
{
	std::vector<Product*> products;
	userMap.insert(std::pair<User*, std::vector<Product*>>(u, products));
	usernameMap.insert(std::pair<std::string, User*>(u->getName(), u));
}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	std::set<Product*> products;
	if(keyMap.find(*terms.begin()) != keyMap.end())
	{
		products = (keyMap.find(*terms.begin()))->second;
	}
	

		//going through every term
	for(vector<std::string>::iterator it = terms.begin() + 1; it != terms.end(); it++)
	{
		std::set<Product*> moreProducts;
		if(keyMap.find(*it) != keyMap.end())
		{
		 moreProducts = (keyMap.find(*it))->second;
		}
			
		//AND search
			
		if(type == 0)
		{
			//check to see if all terms are keys
			products = setIntersection(products,moreProducts);
		}
			
		//OR SEARCH
		else if(type == 1)
		{
			products = setUnion(products,moreProducts);
		}
			
			
	}


	std::vector<Product*> productsRet(products.begin(), products.end());
	return productsRet;

}

	/**
	* Reproduce the database file from the current Products and User values
	*/
void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;

	for(vector<Product*>::iterator it = stock.begin(); it != stock.end(); it++)
	{
		(*it)->dump(ofile);
	}
	ofile << "</products>" << endl;

	ofile << "<users>" << endl;

	for(map<User*, std::vector<Product*>>::iterator it = userMap.begin(); it != userMap.end(); it++)
	{
		(*it).first->dump(ofile);
	}
		ofile << "</users>" << endl;

}

void MyDataStore::addToCart(std::string username, std::vector<Product*>& hits, int hitsIdx)
{


	User* user;
	if(usernameMap.find(username) != usernameMap.end() && hitsIdx > 0 && (unsigned)hitsIdx <= hits.size())
	{
		user = usernameMap.find(username)->second;

		
		if(userMap.find(user) != userMap.end())
		{
			userMap.find(user)->second.push_back(hits[hitsIdx - 1]);
		}
	}
	else
	{
		cout << "Invalid request" << endl;
	}
	
}

void MyDataStore::viewCart(std::string username)
{
	
	User* user;
	if(usernameMap.find(username) != usernameMap.end())
	{
		user = usernameMap.find(username)->second;
	
		vector<Product*> products = userMap.find(user)->second;

		for(unsigned int i = 0; i < products.size(); i++)
		{
			cout <<"Item " << i + 1 << endl;
			cout << products[i]->displayString() << endl;
		}
  }
	else
	{
		cout << "Invalid username" << endl;
	}
	
}

void MyDataStore::buyCart(std::string username)
{
	User* user;
	if(usernameMap.find(username) != usernameMap.end())
	{
		user = usernameMap.find(username)->second;

		vector<Product*> remaining;


		for(vector<Product*>::iterator it = userMap.find(user)->second.begin(); 
				it != userMap.find(user)->second.end(); it++)
		{
			
			//not bought
			if(user->getBalance() < (*it)->getPrice() || (*it)->getQty() == 0)
			{
				remaining.push_back(*it);
			}
			//bought
			else
			{
				//cout << "Bought!" << endl;
				user->deductAmount((*it)->getPrice());
				(*it)->subtractQty(1);
			}
    }

		userMap.find(user)->second = remaining;

	}
	else
	{
		cout << "Invalid username" << endl;
	}
}

