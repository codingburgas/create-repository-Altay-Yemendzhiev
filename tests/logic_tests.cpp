#include "../serviceLayer/logic.h"

#include <cassert>
#include <cstring>

void runDataTests();

static product makeProduct(const char* name, float price, int quantity)
{
    product item = {};
    std::strncpy(item.name, name, maxNameLength - 1);
    item.name[maxNameLength - 1] = '\0';
    item.price = price;
    item.quantity = quantity;
    return item;
}

static void runLogicTests()
{
    product products[3] = {
        makeProduct("brite cola", 1.50f, 20),
        makeProduct("darittas nacho chips", 3.40f, 6),
        makeProduct("sunny oats", 2.10f, 12)
    };

    quickSortByPrice(products, 3);
    assert(std::strcmp(products[0].name, "brite cola") == 0);
    assert(std::strcmp(products[2].name, "darittas nacho chips") == 0);

    quickSortByQuantity(products, 3);
    assert(products[0].quantity == 6);
    assert(products[2].quantity == 20);

    assert(linearSearchByName(products, 3, "nacho") == 0);
    assert(linearSearchByName(products, 3, "missing") == -1);
    assert(linearSearchByQuantity(products, 3, 12, 0) == 1);
    assert(linearSearchByQuantity(products, 3, 100, 0) == -1);

    const float total = calculateTotalValueRecursive(products, 3);
    assert(total > 75.5f && total < 75.7f);

    product jokeProducts[3] = {
        makeProduct("tiny c", 3.00f, 3),
        makeProduct("tiny a", 1.00f, 1),
        makeProduct("tiny b", 2.00f, 2)
    };

    assert(bogoSortProducts(jokeProducts, 3, sortByPrice));
    assert(jokeProducts[0].price <= jokeProducts[1].price);
    assert(jokeProducts[1].price <= jokeProducts[2].price);
}

int main()
{
    runDataTests();
    runLogicTests();
    return 0;
}
