// Quiz 2 (Revised): Custom Exceptions, Function Pointers, and Lambdas with std::vector
#include <iostream>
#include <vector>
#include <string>
#include <exception>

using ProcessItemFunc = bool (*)(int); 

const std::vector<int> data = { 15, 22, 30, 41, 55, 60, 78, 90 };

bool checkMultipleOfTen(int value) {
    return (value % 10 == 0); 
}

class NotValidDataError : public std::exception
{
    std::string msg;
public:
    NotValidDataError():msg("not valid"){}
    const char* what() const noexcept { return msg.c_str();}
};

void searchAndThrow(const std::vector<int>& src,ProcessItemFunc check1, ProcessItemFunc check2){
    bool valid = true;
    for( const auto& data:src){
        valid = check1(data) && check2(data);
        if(!valid) throw NotValidDataError();
    }
}

int main() {
    std::cout << "--- Quiz 2 Start (Vector Version) ---\n";

    try{
        searchAndThrow(data,checkMultipleOfTen,[](int i){return i<80;});
    }
    catch(NotValidDataError& e){
        std::cout<<e.what()<<std::endl;
    }
    std::cout << "--- Quiz 2 End ---\n";
    return 0;
}