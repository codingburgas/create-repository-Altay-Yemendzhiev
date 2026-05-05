#include "../include/logic.h"

#include <cassert>
#include <cstring>

void runDataTests();

static Product makeProduct(const char* name, float price, int quantity)
{
    Product product = {};
    std::strncpy(product.name, name, MAX_NAME_LENGTH - 1);
    product.name[MAX_NAME_LENGTH - 1] = '\0';
    product.price = price;
    product.quantity = quantity;
    return product;
}

static void runLogicTests()
{
    Product products[3] = {
        makeProduct("Brite Cola", 1.50f, 20),
        makeProduct("Darittas Nacho Chips", 3.40f, 6),
        makeProduct("Sunny Oats", 2.10f, 12)
    };

    bubbleSortByPrice(products, 3);
    assert(std::strcmp(products[0].name, "Brite Cola") == 0);
    assert(std::strcmp(products[2].name, "Darittas Nacho Chips") == 0);

    bubbleSortByQuantity(products, 3);
    assert(products[0].quantity == 6);
    assert(products[2].quantity == 20);

    assert(linearSearchByName(products, 3, "nacho") == 0);
    assert(linearSearchByName(products, 3, "missing") == -1);

    const float total = calculateTotalValueRecursive(products, 3);
    assert(total > 75.5f && total < 75.7f);
}

int main()
{
    runDataTests();
    runLogicTests();
    return 0;
}
