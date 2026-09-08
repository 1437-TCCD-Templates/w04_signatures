// signatures.cpp
//
// COSC 1437 - Week 4 - Signature Interrogation
//
// Nine functions. Each one is handed a variable, and each one tries to
// change it. Some succeed. Some do not. Some will not even compile.
//
// DO NOT BUILD THIS YET.
//
// Read every function first. On your prediction sheet, write down what
// you think happens to the caller's variable for each one, and why.
// Only after you have predicted all nine should you build and run.
//
// Build with:  g++ -std=c++20 -Wall signatures.cpp -o signatures

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// ---------------------------------------------------------------------
// A small record, so we can see whether user-defined types behave the
// same way the built-in ones do.
// ---------------------------------------------------------------------
struct Item {
    std::string name;
    int stock;
};

// ---------------------------------------------------------------------
// 1
// ---------------------------------------------------------------------
void addTenToValue(int quantity) {
    quantity += 10;
}

// ---------------------------------------------------------------------
// 2
// ---------------------------------------------------------------------
void addTenToReference(int& quantity) {
    quantity += 10;
}

// ---------------------------------------------------------------------
// 3
//
// This one is deliberately broken. Read it, predict what the compiler
// will say, then leave it commented out so the rest of the program
// still builds. Uncomment it only when your instructor says to.
// ---------------------------------------------------------------------
// void addTenToConstReference(const int& quantity) {
//     quantity += 10;
// }

// ---------------------------------------------------------------------
// 4
// ---------------------------------------------------------------------
void addTenThroughPointer(int* quantity) {
    *quantity += 10;
}

// ---------------------------------------------------------------------
// 5
// ---------------------------------------------------------------------
void zeroOutVectorByValue(std::vector<int> readings) {
    for (auto& reading : readings) {
        reading = 0;
    }
}

// ---------------------------------------------------------------------
// 6
// ---------------------------------------------------------------------
void zeroOutVectorByReference(std::vector<int>& readings) {
    for (auto& reading : readings) {
        reading = 0;
    }
}

// ---------------------------------------------------------------------
// 7
// ---------------------------------------------------------------------
void restockByValue(Item item) {
    item.stock = 99;
}

// ---------------------------------------------------------------------
// 8
// ---------------------------------------------------------------------
void restockByReference(Item& item) {
    item.stock = 99;
}

// ---------------------------------------------------------------------
// 9
//
// This one does not try to change anything. The question here is
// different: what does it cost to call?
// ---------------------------------------------------------------------
int countReadings(const std::vector<int>& readings) {
    return static_cast<int>(readings.size());
}

// ---------------------------------------------------------------------
// Reporting helpers. You do not need to modify anything below this
// line, but you are welcome to read it.
// ---------------------------------------------------------------------
void report(int number, const std::string& label, int before, int after) {
    std::cout << std::setw(2) << number << ".  " << std::setw(28) << std::left
              << label << std::right << "before: " << std::setw(4) << before
              << "   after: " << std::setw(4) << after
              << (before == after ? "   UNCHANGED" : "   CHANGED") << '\n';
}

void reportVector(int number, const std::string& label,
                  const std::vector<int>& before,
                  const std::vector<int>& after) {
    std::cout << std::setw(2) << number << ".  " << std::setw(28) << std::left
              << label << std::right << "before: ";

    for (int value : before) {
        std::cout << value << ' ';
    }

    std::cout << "  after: ";

    for (int value : after) {
        std::cout << value << ' ';
    }

    std::cout << (before == after ? "  UNCHANGED" : "  CHANGED") << '\n';
}

int main() {
    std::cout << "=== SIGNATURE INTERROGATION ===\n\n";

    // -----------------------------------------------------------------
    // 1  void addTenToValue(int quantity)
    // -----------------------------------------------------------------
    int quantity1{5};
    int before1{quantity1};
    addTenToValue(quantity1);
    report(1, "int", before1, quantity1);

    // -----------------------------------------------------------------
    // 2  void addTenToReference(int& quantity)
    // -----------------------------------------------------------------
    int quantity2{5};
    int before2{quantity2};
    addTenToReference(quantity2);
    report(2, "int&", before2, quantity2);

    // -----------------------------------------------------------------
    // 3  void addTenToConstReference(const int& quantity)
    // -----------------------------------------------------------------
    std::cout << " 3.  const int&                 "
              << "does not compile - see the source\n";

    // -----------------------------------------------------------------
    // 4  void addTenThroughPointer(int* quantity)
    // -----------------------------------------------------------------
    int quantity4{5};
    int before4{quantity4};
    addTenThroughPointer(&quantity4);
    report(4, "int*", before4, quantity4);

    std::cout << '\n';

    // -----------------------------------------------------------------
    // 5  void zeroOutVectorByValue(std::vector<int> readings)
    // -----------------------------------------------------------------
    std::vector<int> readings5{3, 7, 11};
    std::vector<int> before5{readings5};
    zeroOutVectorByValue(readings5);
    reportVector(5, "vector<int>", before5, readings5);

    // -----------------------------------------------------------------
    // 6  void zeroOutVectorByReference(std::vector<int>& readings)
    // -----------------------------------------------------------------
    std::vector<int> readings6{3, 7, 11};
    std::vector<int> before6{readings6};
    zeroOutVectorByReference(readings6);
    reportVector(6, "vector<int>&", before6, readings6);

    std::cout << '\n';

    // -----------------------------------------------------------------
    // 7  void restockByValue(Item item)
    // -----------------------------------------------------------------
    Item item7{"Pretzels", 3};
    int before7{item7.stock};
    restockByValue(item7);
    report(7, "Item", before7, item7.stock);

    // -----------------------------------------------------------------
    // 8  void restockByReference(Item& item)
    // -----------------------------------------------------------------
    Item item8{"Pretzels", 3};
    int before8{item8.stock};
    restockByReference(item8);
    report(8, "Item&", before8, item8.stock);

    std::cout << '\n';

    // -----------------------------------------------------------------
    // 9  int countReadings(const std::vector<int>& readings)
    // -----------------------------------------------------------------
    std::vector<int> readings9{3, 7, 11, 15, 19};
    std::cout << " 9.  const vector<int>&         "
              << "returned " << countReadings(readings9)
              << ", changed nothing, copied nothing\n";

    std::cout << "\n=== END ===\n";

    return 0;
}
