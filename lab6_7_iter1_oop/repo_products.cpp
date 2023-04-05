#include "repo_products.h"

void RepoProducts::addProduct(ElementType product) {
	if (this->values.size() < this->values.capacity())
	{
		this->values.push_back(product);
		return;
	}
	throw "Full Repo";
}

void RepoProducts::deleteProduct(int position) {

}

void RepoProducts::updateProduct(ElementType product, int position) {

}

vector<ElementType> RepoProducts::copyOfVector() {

}

int RepoProducts::getLenght() {

}

ElementType RepoProducts::getElement(int position) {

}