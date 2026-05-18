#include "../dataAccessLayer/data.h"

#include <cassert>
#include <cstring>

static product makeProduct(const char* name, float price, int quantity)
{
    product item = {};
    std::strncpy(item.name, name, maxNameLength - 1);
    item.name[maxNameLength - 1] = '\0';
    item.price = price;
    item.quantity = quantity;
    return item;
}

void runDataTests()
{
    assert(loadFromFile("assets/products.csv"));
    assert(getProductCount() == 80);

    product loadedItem = {};
    assert(getProduct(0, &loadedItem));
    assert(std::strcmp(loadedItem.name, "darittas nacho chips mini pack") == 0);

    assert(addProduct(makeProduct("test chips", 2.50f, 10)));
    assert(addProduct(makeProduct("test soda", 1.20f, 5)));
    assert(getProductCount() == 82);

    product item = {};
    assert(getProduct(80, &item));
    assert(std::strcmp(item.name, "test chips") == 0);

    assert(updateProduct(80, makeProduct("updated chips", 2.75f, 8)));
    assert(getProduct(80, &item));
    assert(std::strcmp(item.name, "updated chips") == 0);
    assert(item.quantity == 8);

    assert(removeProduct(81));
    assert(getProductCount() == 81);
}
