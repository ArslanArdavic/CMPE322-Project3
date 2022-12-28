#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> parseStringToArray(std::string s);

enum customerStatus {created, ready, waiting, processing};

class Company {
    private:
        std::string _name;
        int _balance;
        int _transactionCount;

    public:
        Company(std::string name){
            _name = name; 
            _balance = 0;
            _transactionCount = 0;
        }
        int getBalance(){return _balance;}
        void receivePayment(int receiveAmount){ 
            _balance += receiveAmount;
            _transactionCount++;
        }
        void toConsole(){ std::cout << "Company " << _name  << " | Balance = " << _balance << " , Transactions = " << _transactionCount << std::endl;}

};

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
        void toConsole(){ std::cout << "Customer " << _id  << ": [" << _sleepDuration << ","<< _payFromMachineID << ","<< _payToCompany << ","<< _payAmount << ","<< "status="<< status << "]"<< std::endl;}
};

class VendingMachine {
    private:
        int _id;
        int _transactionCount;
    
    public:
        VendingMachine(int id){
            _id = id;
            _transactionCount = 0;
        };
        void toConsole(){std::cout <<"Vending Machine " << _id << " |" <<" Transactions = " <<  _transactionCount << std::endl;}
        void processPayment(){_transactionCount++;}
};

class Transaction{
    private:
        int _id;
        int _issuedByMachineID;
        std::string _issuedByCompanyName;
        int _requestedFromCustomerID;
    public:
        Transaction(int id,int issuedByMachineID, std::string issuedByCompanyName, int requestedFromCustomerID){
            _id = id;
            _issuedByMachineID = issuedByMachineID;
            _issuedByCompanyName = issuedByCompanyName;
            _requestedFromCustomerID = requestedFromCustomerID;
        }
        void toConsole(){ std::cout<<"Transaction "<< _id << " | " << "ByMachine:" << _issuedByMachineID << " , ByCompany:" << _issuedByCompanyName << " , Customer:" <<_requestedFromCustomerID << std::endl ;}
}



/*  main() function consists of 4 parts:
.
.                                1.COMPANIES
.                                2.MACHINES
.                                3.CUSTOMERS
.                                4.TRANSACTIONS     
.                
*/                                 

int main(){

    /*                           --COMPANIES--
    Create 5 different service provider companies and keep'em in an array.*/
    Company* COMPANIES[5];
    Company* Bob = new Company("Bob");                  COMPANIES[0]=Bob;
    Company* Dave = new Company("Dave");                COMPANIES[1]=Dave;
    Company* Kevin = new Company("Kevin");              COMPANIES[2]=Kevin;
    Company* Otto = new Company("Otto");                COMPANIES[3]=Otto;
    Company* Stuart = new Company("Stuart");            COMPANIES[4]=Stuart;


    /*                           --MACHINES--
    Create 10 different service provider vending machines and keep'em in an array.*/
    VendingMachine* MACHINES[10];
    for(int i=0;i<10;i++){
        VendingMachine* mach = new VendingMachine(i);   
        MACHINES[i]=mach;
    }

    /*                           --CUSTOMERS--
    Create customerCount many Customer object instances as specified in the input file 
    .                                                     and keep'em in an array.*/
    int customerCount;
    static int customersCreated=0;

    std::ifstream ReadFile("input1.txt");                 //  First line of input file, 
    std::string firstLine;                                //  specifies customerCount.
    getline(ReadFile, firstLine);
    customerCount = std::stoi(firstLine);

    Customer* CUSTOMERS[customerCount];                   //  Create array.

    for(int i=0; i<customerCount;i++){
        //Read a new line and parse required info construct object respectively.
        std::string line; getline(ReadFile, line); std::vector<std::string> lineArray = parseStringToArray(line);
        int sleepDuration=std::stoi(lineArray[0]); int payFromMachineID=std::stoi(lineArray[1]);
        std::string payToCompany = lineArray[2]; int payAmount=std::stoi(lineArray[3]);

        Customer* customer = new Customer(customersCreated++, sleepDuration, payFromMachineID, payToCompany, payAmount);
        CUSTOMERS[i] = customer;
    }


    /*                           --TRANSACTIONS--
    Here simulation runs, prepayments documented as transactions are made. */
    
    
    for(int i=0;i<5;i++)
        COMPANIES[i] -> toConsole();

    for(int i=0;i<customerCount;i++)
        CUSTOMERS[i] -> toConsole();

    for(int i=0;i<10;i++)
        MACHINES[i]-> toConsole();

       



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