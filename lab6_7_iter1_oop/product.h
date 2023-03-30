#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Product {

private:
	string productName;
	string productType;
	float productPrice;
	string productProducer;

public:
	Product(string name, string type, float price, string producer) :
		productName{name},
		productType{type},
		productPrice{price},
		productProducer{producer}
	{}

	Product(const Product& product) :
		productName{ product.productName },
		productType{ product.productType },
		productPrice{ product.productPrice },
		productProducer{ product.productProducer }
	{
		cout << "!!!!!!!!!!!!!!!!\n";
	}
};