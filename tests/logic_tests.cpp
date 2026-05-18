#include "../serviceLayer/logic.h"

#include <cassert>
#include <cstdio>
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

static void testBubbleSort()
{
    product products[3] = {
        makeProduct("C", 30.0f, 5),
        makeProduct("A", 10.0f, 15),
        makeProduct("B", 20.0f, 10)
    };

    bubbleSortProducts(products, 3, sortByPrice);
    assert(products[0].price == 10.0f);
    assert(products[1].price == 20.0f);
    assert(products[2].price == 30.0f);

    bubbleSortProducts(products, 3, sortByQuantity);
    assert(products[0].quantity == 5);
    assert(products[1].quantity == 10);
    assert(products[2].quantity == 15);
}

static void testBinarySearch()
{
    product products[4] = {
        makeProduct("A", 10.0f, 5),
        makeProduct("B", 20.0f, 10),
        makeProduct("C", 30.0f, 15),
        makeProduct("D", 40.0f, 20)
    };

    // Searching by price (array must be sorted by price)
    assert(binarySearchByPrice(products, 4, 30.0f) == 2);
    assert(binarySearchByPrice(products, 4, 10.0f) == 0);
    assert(binarySearchByPrice(products, 4, 40.0f) == 3);
    assert(binarySearchByPrice(products, 4, 50.0f) == -1);

    // Searching by quantity (array must be sorted by quantity)
    assert(binarySearchByQuantity(products, 4, 10) == 1);
    assert(binarySearchByQuantity(products, 4, 5) == 0);
    assert(binarySearchByQuantity(products, 4, 20) == 3);
    assert(binarySearchByQuantity(products, 4, 25) == -1);
}

static void testDuplicateDetection()
{
    // We need to use the actual inventory for this test as findDuplicateProducts uses getInventory()
    while (getProductCount() > 0)
    {
        removeProduct(0);
    }

    addNewProduct("Apple", 1.0f, 10);
    addNewProduct("Banana", 2.0f, 20);
    addNewProduct("Apple", 1.5f, 5); // Duplicate name
    addNewProduct("Cherry", 3.0f, 15);
    addNewProduct("Banana", 2.5f, 8); // Duplicate name

    int duplicates[10] = {};
    int count = findDuplicateProducts(duplicates, 10);

    assert(count == 2);
    // findDuplicateProducts returns the index of the LATER occurrence
    assert(duplicates[0] == 2); // Second "Apple"
    assert(duplicates[1] == 4); // Second "Banana"
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

    testBubbleSort();
    testBinarySearch();
    testDuplicateDetection();
}

int main()
{
    runDataTests();
    runLogicTests();

    std::printf("All tests passed!\n");

    return 0;
}
