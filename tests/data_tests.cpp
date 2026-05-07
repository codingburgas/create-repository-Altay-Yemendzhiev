#include "../include/data.h"

#include <cassert>
#include <cstring>

static Product makeProduct(const char* name, float price, int quantity)
{
    Product product = {};
    std::strncpy(product.name, name, MAX_NAME_LENGTH - 1);
    product.name[MAX_NAME_LENGTH - 1] = '\0';
    product.price = price;
    product.quantity = quantity;
    return product;
}

void runDataTests()
{
    assert(loadFromFile("resources/products.csv"));
    assert(getProductCount() == 300);

    Product loadedProduct = {};
    assert(getProduct(0, &loadedProduct));
    assert(std::strcmp(loadedProduct.name, "Darittas Nacho Chips Mini Pack") == 0);

    assert(addProduct(makeProduct("Test Chips", 2.50f, 10)));
    assert(addProduct(makeProduct("Test Soda", 1.20f, 5)));
    assert(getProductCount() == 302);

    Product product = {};
    assert(getProduct(300, &product));
    assert(std::strcmp(product.name, "Test Chips") == 0);

    assert(updateProduct(300, makeProduct("Updated Chips", 2.75f, 8)));
    assert(getProduct(300, &product));
    assert(std::strcmp(product.name, "Updated Chips") == 0);
    assert(product.quantity == 8);

    assert(removeProduct(301));
    assert(getProductCount() == 301);
}
