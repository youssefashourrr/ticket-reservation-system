#include "Admin.h"


Admin::Admin() {}


void Admin::setKey(const string& key){
	this->key = key;
} 


string Admin::getKey() const {
	return key;
}
