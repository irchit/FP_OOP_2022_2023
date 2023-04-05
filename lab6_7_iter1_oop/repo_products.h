#include "product.h"
#include <vector>
#include <string>

using std::vector;

typedef Product ElementType;

class RepoProducts
{

private:
	vector<ElementType> values;

public:
	RepoProducts(int capacity)
	{
		this->values.reserve(capacity);
	};
	void addProduct(ElementType product);
	void deleteProduct(int position);
	void updateProduct(ElementType product, int position);
	vector<ElementType> copyOfVector();
	int getLenght();
	ElementType getElement(int position);

};