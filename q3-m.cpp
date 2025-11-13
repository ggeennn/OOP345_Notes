//[Includes]
#include <fstream>
#include <vector>
#include <iostream>

//[Class Definition]
class StockItem {
    int sku;
    char desc[40];
    double price;
    int quantity;
    // ... public methods, constructors ...   
    // operator<< must be overloaded for text output
    friend std::ostream& operator<<(std::ostream& os, const StockItem& item);
};

//[Constants]
const long recordSize = sizeof(StockItem);

//[File Opening]
// Binary Read/Write (Must be fstream)，不可以省略in/out
std::fstream binFile("records.dat", std::ios::in | std::ios::out | std::ios::binary);
// Text Output (Truncate)
std::ofstream txtFile("extracted.txt"); //可以省略 std::ios::out | std::ios::trunc
// Error Check
if (!binFile) {
    std::cerr << "Error opening .dat file" << std::endl;
    return 1;
}
if (!txtFile) {
    std::cerr << "Error opening .txt file" << std::endl;
    return 1;
}

//[Get Total Record Count]
binFile.seekg(0, std::ios::end);
long fileSize = binFile.tellg();
size_t totalRecords = fileSize / sizeof(StockItem);
binFile.seekg(0, std::ios::beg); // Reset pointer to start

//[Part A: Random Read (seekg) and Text Write]
StockItem tempItem;
std::vector<int> indices = { 5, 50, 99 }; // 6th, 51st, 100th record
for (int index : indices) {
    // 1. Calculate Offset
    long offset = index * sizeof(StockItem);
    // 2. Seek (Read Pointer)
    binFile.seekg(offset, std::ios::beg);
    // 3. Binary Read (Raw)
    binFile.read(reinterpret_cast<char*>(&tempItem), recordSize);
    // 4. Text Write (Formatted)
    if (binFile) { // Check if read was successful
        txtFile << "Index " << index << ": " << tempItem << "\n";
    } else {
        binFile.clear(); // Clear error state (e.g., EOF)
    }
}

//[Part B: Random Write/Overwrite (seekp)]
// 1. Create Data
StockItem updatedItem(9999, "UPDATED", 123.45, 10);
int updateIndex = 75; // 76th record
// 2. Calculate Offset
long updateOffset = updateIndex * sizeof(StockItem);
// 3. Seek (Write Pointer)
binFile.seekp(updateOffset, std::ios::beg);
// 4. Binary Write (Raw)
binFile.write(reinterpret_cast<const char*>(&updatedItem), recordSize);

//[Part C: Verification Read]
// 1. Seek (Read Pointer) to the same spot
binFile.seekg(updateOffset, std::ios::beg);
// 2. Binary Read (Raw)
binFile.read(reinterpret_cast<char*>(&tempItem), recordSize);
// 3. Display to console
std::cout << "Verified Record " << updateIndex << ":\n" << tempItem << std::endl;

//[Cleanup]可以不写
binFile.close();
txtFile.close();