#include "product.h"

string Product::productToString() {
	string productString = "";
	productString += this->productName + " : ";
	productString += this->productType + " : ";
	productString += to_string(this->productPrice) + "RON : ";
	productString += this->productProducer;
	return productString;
}

bool compareByName(Product& product1, Product& product2) {
	return product1.getProductName() < product2.getProductName();
}

bool compareByType(Product& product1, Product& product2) {
	return product1.getProductType() < product2.getProductType();
}

bool compareByPrice(Product& product1, Product& product2) {
	return product1.getProductPrice() < product2.getProductPrice();

}

bool compareByProducer(Product& product1, Product& product2) {
	return product1.getProductProducer() < product2.getProductProducer();
}

void testClassProduct()
{
	string name1 = "Cascaval";
	string type1 = "Lactate";
	float price1 = 15.99f;
	string  producer1 = "Delaco";
	
	Product product1 = Product(name1, type1, price1, producer1);
	assert(product1.getProductName() == name1);
	assert(product1.getProductType() == type1);
	assert(abs(product1.getProductPrice() - price1) < 0.001f);
	assert(product1.getProductProducer() == producer1);
	string product1ExpectedString = name1 + " : " + type1 + " : " + to_string(price1) + "RON : " + producer1;
	assert(product1.productToString() == product1ExpectedString);

	Product product2CopyOfProduct1 = Product(product1);
	assert(product1.getProductName() == product2CopyOfProduct1.getProductName());
	assert(product1.getProductType() == product2CopyOfProduct1.getProductType());
	assert(abs(product1.getProductPrice() - product2CopyOfProduct1.getProductPrice()) < 0.001f);
	assert(product1.getProductProducer() == product2CopyOfProduct1.getProductProducer());
	assert(product1.productToString() == product2CopyOfProduct1.productToString());

	string newType = "Branzeturi";
	float newPrice = 19.99f;
	string newProducer = "Dalia";
	product1.setProductPrice(newPrice);
	product1.setProductProducer(newProducer);
	product1.setProductType(newType);
	assert(product1.getProductType() == newType);
	assert(abs(product1.getProductPrice() - newPrice) < 0.001f);
	assert(product1.getProductProducer() == newProducer);

	Product product2 = Product(product2CopyOfProduct1);
	assert(!compareByName(product1, product2));
	assert(compareByType(product1, product2));
	assert(compareByPrice(product2, product1));
	assert(compareByProducer(product1, product2));
}