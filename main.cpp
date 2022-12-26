#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> parseStringToArray(std::string s);

enum customerStatus {created, ready, waiting, processing};

class Customer {
    private:
        int _id;
        int _sleepDuration;
        int _payFromMachineID;
        std::string _payToCompany;   
        int _payAmount;
        customerStatus status;

    public:
        Customer(int id, int sleepDuration, int payFromMachineID, std::string payToCompany, int payAmount){
            _id = id;
            _sleepDuration = sleepDuration;
            _payFromMachineID = payFromMachineID;
            _payToCompany = payToCompany;
            _payAmount = payAmount;
            status = created;
        }
        void toConsole(){
            std::cout << "Customer " << _id  << ": [" << _sleepDuration << ","<< _payFromMachineID << ","<< _payToCompany << ","<< _payAmount << ","<< status << "]"<< std::endl;
        }
};


int main(){
    int customerCount;
    static int customersCreated=0;

    /*Open input file and read first line, integer value of customerCount.*/
    std::ifstream ReadFile("input1.txt");
    std::string firstLine;
    getline(ReadFile, firstLine);
    customerCount = std::stoi(firstLine);

    /*Create array of pointers to Customer object instances*/
    Customer* customerPtrs[customerCount];

    /*Create customerCount many Customer object instances with respect to input file.*/
    for(int i=0; i<customerCount;i++){

        /*Read a new line and parse required info.*/
        std::string line;
        getline(ReadFile, line);
        
        std::vector<std::string> lineArray = parseStringToArray(line);
        int sleepDuration=std::stoi(lineArray[0]); 
        int payFromMachineID=std::stoi(lineArray[1]);
        std::string payToCompany = lineArray[2];
        int payAmount=std::stoi(lineArray[3]);

        Customer* customerPtr = new Customer(customersCreated++, sleepDuration, payFromMachineID, payToCompany, payAmount);
        customerPtrs[i] = customerPtr;
        customerPtrs[i] -> toConsole();
    }
    return 0;
}


std::vector<std::string> parseStringToArray(std::string s){
    std::vector<std::string> v(4);
    std::string delimiter=",";
    size_t pos = 0;
    std::string token;
    int index = 0; 
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        v[index] = token;
        index++;
        s.erase(0, pos + delimiter.length());
    }
    v[index] = s;

    return v;
} 