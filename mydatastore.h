#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore {

public:

	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);

	void addToCart(std::string username, std::vector<Product*>& hits, int hitsIdx);
	void viewCart(std::string username);
	void buyCart(std::string username);
	/**
	* Performs a search of products whose keywords match the given "terms"
	*  type 0 = AND search (intersection of results for each term) while
	*  type 1 = OR search (union of results for each term)
	*/
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	/**
	* Reproduce the database file from the current Products and User values
	*/
	void dump(std::ostream& ofile);
	

private:

	std::map<std::string, User*> usernameMap;
	std::map<User*, std::vector<Product*>> userMap;
	std::vector<Product*> stock;
	std::map<std::string,std::set<Product*>> keyMap;

};


#endif