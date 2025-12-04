// quiz3_solution.cpp
// (Reference Solution for Quiz 3)

#include "StockItem.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace oop345;

int main() {
    // Size of one record. This is crucial for calculating offsets.
    const long recordSize = sizeof(StockItem);

    // TODO 1: Open 'records.dat' for BINARY read/write operations (ios::in | ios::out | ios::binary)
    //         Check if the file opened successfully. If not, print an error and exit(1).
    std::fstream binFile("records.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!binFile) {
        std::cerr << "Error: Could not open records.dat for read/write." << std::endl;
        return 1;
    }

    // TODO 2: Open 'extracted.txt' for TEXT output (ios::out | ios::trunc)
    //         Check if the file opened successfully. If not, print an error and exit(1).
    std::ofstream txtFile("extracted.txt", std::ios::out | std::ios::trunc);
    if (!txtFile) {
        std::cerr << "Error: Could not open extracted.txt for output." << std::endl;
        binFile.close(); // Close the already opened file
        return 1;
    }

    // --- Part A: Extract Specific Records ---

    std::cout << "Part A: Extracting records..." << std::endl;
    StockItem tempItem; // Use this object to read data into

    // We want to extract records at these specific indices:
    std::vector<int> indicesToExtract = { 5, 50, 99, 2 };

    for (int index : indicesToExtract) {
        // TODO 3: Calculate the byte offset for the 'index'.
        //         Offset = index * recordSize
        long offset = index * recordSize;

        // TODO 4: Seek to the calculated offset from the beginning (ios::beg)
        //         Use binFile.seekg()
        binFile.seekg(offset, std::ios::beg);

        // Check for seek errors (e.g., seeking past end-of-file)
        if (!binFile) {
             std::cerr << "Error seeking to index " << index << std::endl;
             binFile.clear(); // Clear error flags to continue loop
             continue; // Skip this index
        }

        // TODO 5: Read one StockItem record from binFile into tempItem
        //         Use tempItem.read()
        tempItem.read(binFile);

        // Check for read errors (e.g., EOF reached prematurely)
         if (!binFile) {
             std::cerr << "Error reading at index " << index << std::endl;
             binFile.clear();
             continue;
         }

        // TODO 6: Write the extracted tempItem to the TEXT file (txtFile)
        //         Remember to add a newline in the text file for readability.
        //         Use the overloaded operator<< (e.g., txtFile << tempItem << ...)
        txtFile << "Record at index " << index << ":\n"
                << tempItem << "\n---\n";
    }

    std::cout << "Extraction complete. Check 'extracted.txt'." << std::endl;
    txtFile.close(); // Done with the text file


    // --- Part B: Update a Record ---

    std::cout << "\nPart B: Updating record at index 75..." << std::endl;

    // TODO 7: Create a new StockItem to overwrite an existing record.
    //         Use SKU: 9999, Desc: "UPDATED RECORD", Price: 123.45, Qty: 10
    StockItem updatedItem(9999, "UPDATED RECORD", 123.45, 10);


    // TODO 8: Calculate the byte offset for index 75.
    long updateOffset = 75 * recordSize;


    // TODO 9: Seek to the 'updateOffset' from the beginning (ios::beg)
    //         IMPORTANT: Use binFile.seekp() because we are 'putting' (writing) data.
    binFile.seekp(updateOffset, std::ios::beg);
    if (!binFile) {
         std::cerr << "Error: seekp failed before writing update." << std::endl;
         binFile.close();
         return 1;
    }

    // TODO 10: Write the 'updatedItem' to the binary file (binFile)
    //          Use updatedItem.write()
    updatedItem.write(binFile);
    if (!binFile) {
         std::cerr << "Error: write failed during update." << std::endl;
         binFile.close();
         return 1;
    }

    // --- Part C: Verify the Update ---

    std::cout << "\nPart C: Verifying update..." << std::endl;

    // NOTE: After a write, the 'put' and 'get' pointers might be in different
    // places or their state might be implementation-defined.
    // It is SAFEST to explicitly seekg() to where you want to read.

    // TODO 11: We are already at the end of the record we just wrote.
    //          To read it back, we must seekg() to the *same* offset (updateOffset).
    //          Use binFile.seekg()
    binFile.seekg(updateOffset, std::ios::beg);
     if (!binFile) {
         std::cerr << "Error: seekg failed before verification read." << std::endl;
         binFile.close();
         return 1;
    }

    // TODO 12: Read the record at that position back into 'tempItem'
    //          Use tempItem.read()
    tempItem.read(binFile);
     if (!binFile) {
         std::cerr << "Error: read failed during verification." << std::endl;
         binFile.close();
         return 1;
    }

    // TODO 13: Display the 'tempItem' to the console (std::cout) to verify it matches
    //          the 'updatedItem' data.
    std::cout << "Record at index 75 is now:\n" << tempItem << std::endl;


    // --- Cleanup ---

    // TODO 14: Close the binary file (binFile)
    binFile.close();

    std::cout << "\nQuiz complete." << std::endl;
    return 0;
}





std::fstream bfile('b.bin',std::ios::in|std::ios::out|std::ios::binary);
std::ofstream tfile('t.txt');
if(bfile){
    bfile.seekg(0,std::ios::end);
    size_t rsize = bfile.tellg()/sizeof(Obj);
    size_t mid = (rsize-rsize%2)/2;
    bfile.seekg(mid*sizeof(Obj),std::ios::beg);
    Obj temp;
    bfile.read(reinterpret_cast<char*>(&temp),sizeof(Obj));
    if(tfile) tfile<<temp;
    Obj temp2;
    bfile.seekp(mid*sizeof(Obj),std::ios::beg);
    bfile.write(reinterpret_cast<const char*>(&temp2),sizeof(Obj));
}