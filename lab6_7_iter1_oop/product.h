#pragma once
#include <string>
#include <cassert>
#include <iostream>

using std::string;
using std::cout;
using std::to_string;

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
	{}

	string getProductName()
	{
		return this->productName;
	}

	string getProductType()
	{
		return this->productType;
	}

	float getProductPrice()
	{
		return this->productPrice;
	}

	string getProductProducer()
	{
		return this->productProducer;
	}

	void setProductType(string newType)
	{
		this->productType = newType;
	}

	void setProductPrice(float newPrice)
	{
		this->productPrice = newPrice;
	}

	void setProductProducer(string newProducer) 
	{
		this->productProducer = newProducer;
	}

	string productToString();
};

bool compareByName(Product&, Product&);
bool compareByType(Product&, Product&);
bool compareByPrice(Product&, Product&);
bool compareByProducer(Product&, Product&);

void testClassProduct();

