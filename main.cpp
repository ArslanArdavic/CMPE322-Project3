/* TODO: Implement Output Logs.*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>

std::mutex CRITICALSECTION;

#define SIZEMAXCUSTOMERS 300
#define COMPANYCOUNT     5
#define MACHINECOUNT     10+1

std::string inputFileName="input1.txt";
int     CUSTOMERCOUNT        ;                                      
static int customersCreated=0;
enum  customerStatus{processing, ready, done};
enum  banks{bob, dave, kevin, otto, stuart, null};

void createNewMachine(int GenerationLoopCounter);
void createNewCustomerThread(int GenerationLoopCounter, int id, int sleepDuration, int payFromMachineID, std::string payToCompany, int payAmount);
void printDetailsOfMachineWithIndex(int i);
void printDetailsOfCustomerWithIndex(int i);
std::vector<std::string> parseStringToArray(std::string s);
banks hashit (std::string const& inString);

class Transaction {
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
};

class Company {
    private:
        std::string _name;
        int _balance;
        int _transactionCount;
        std::vector<int> customersServedQUEUE;                                                                    

    public:
        Company(std::string name){
            _name = name; 
            _balance = 0;
            _transactionCount = 0;
        }
        int getBalance(){return _balance;}
        void receivePayment(int receiveAmount, int fromCustomerID){ 
            _balance += receiveAmount;
            _transactionCount++;
            customersServedQUEUE.push_back(fromCustomerID);
            std::cout << '\t'<<  _name <<" Company recieved payment." << std::endl;
        }
        void toConsole(){ std::cout << "    Company " << _name  << " | Balance = " << _balance << " , Transactions = " << _transactionCount << std::endl;}

};Company* COMPANIES[COMPANYCOUNT];

class VendingMachine {
    private:
        int _id;
        std::thread::id _threadID;
        int _transactionCount;
        int _requestCount;
        bool _available=true;
    
    public:
        VendingMachine(int id){
            _id = id;
            _threadID = std::this_thread::get_id();
            _transactionCount = 0;
            _requestCount = 0;
            if (id==0){
                _available = !_available;
            }
        };
        void toConsole(){   
            std::cout << "    " << "MachineThreadID: "<< _threadID <<std::endl<<"        ";
            std::cout <<"Vending Machine " << _id << " | " << "Requests = " << _requestCount << ", Transactions = " <<  _transactionCount <<", status="<< _available << std::endl;
        }
        customerStatus processPayment(int customerID, std::string companyName, int amount){                                                                                
            /*                                                                 TODO                                                                 */
            banks bank = hashit(companyName);

            COMPANIES[bank] -> receivePayment(amount, customerID);
            ++_transactionCount;
            return done;
            }

};VendingMachine* MACHINES[MACHINECOUNT];

class Customer {
    private:
        int _id;
        std::thread::id _threadID;

        int _sleepDuration;
        int _payFromMachineID;
        std::string _payToCompany;   
        int _payAmount;

        customerStatus _status;
        Transaction* _ticket;

    public:
        Customer(int sleepDuration, int payFromMachineID, std::string payToCompany, int payAmount){
            _id = ++customersCreated;
            _sleepDuration = sleepDuration;
            _payFromMachineID = payFromMachineID;
            _payToCompany = payToCompany;
            _payAmount = payAmount;
            _status = ready;
            _threadID = std::this_thread::get_id();            
        }
        int getSleepDuration(){     return _sleepDuration;}
        int getPayFromMachineID(){  return _payFromMachineID;}
        std::string getPayToCompany(){      return _payToCompany;}
        int getPayAmount(){         return _payAmount;}
        int getID(){                return _id;}

        void buyTicket(){           
            CRITICALSECTION.lock();
            /*Critical Section*/
                _status = processing;
                std::cout << _sleepDuration << "ms slept."<<" Payment process started by Customer["<< _id << "]" 
                          << "at Machine["<< _payFromMachineID << "]" << std::endl;
                _status = MACHINES[_payFromMachineID] -> processPayment(_id, _payToCompany, _payAmount);
            
            CRITICALSECTION.unlock();

        }

        void toConsole(){ 
            std::cout << "    " << "CustomerThreadID: "<< _threadID <<std::endl<<"        ";
            std::cout << "Customer "    << _id  << ": [" << _sleepDuration << ","<< _payFromMachineID << 
                                                   ","<< _payToCompany  << ","<< _payAmount        << ","<< "status="<< _status << "]"<< std::endl;
        }

};Customer* CUSTOMERS[SIZEMAXCUSTOMERS]; 


/*  main() function consists of 4 UPPERCASE fundamental parts.*/       
int main(){

/*                             main thread                                                                           */
    /*std::thread::id threadID = std::this_thread::get_id();std::cout << "printThreadID: "<< threadID <<" main()\n"; */

/*                           -- COMPANIES--
    Create 5 different service provider companies and append to array.                          */
    Company* Bob    = new Company("Bob"   ) ;                   COMPANIES[0]=Bob;
    Company* Dave   = new Company("Dave"  ) ;                   COMPANIES[1]=Dave;
    Company* Kevin  = new Company("Kevin" ) ;                   COMPANIES[2]=Kevin;
    Company* Otto   = new Company("Otto"  ) ;                   COMPANIES[3]=Otto;
    Company* Stuart = new Company("Stuart") ;                   COMPANIES[4]=Stuart;

/*                           -- MACHINES --
    Create 10 different service provider vending machines and append to array.                  *///THREAD processing machine affaires.
    std::vector<std::thread> threadsOfMachines;                                                  // 

    for(int i=0;i<MACHINECOUNT;i++){
        threadsOfMachines.push_back(std::thread(createNewMachine, i));                           //  Create new thread and append to array.
    }
    for(int j=0;j<MACHINECOUNT;j++){
        threadsOfMachines[j].join();                                                             //  Make threads join.
    }

/*                           -- CUSTOMERS--
    Create CUSTOMERCOUNT many Customer object instances as specified in the input file 
    .                                                                  and keep'em in an array.  */  

    std::ifstream ReadFile(inputFileName);                                                                           //              First line of input file, 
    std::string firstLine;                                                                                          //              specifies  customerCount.
    getline(ReadFile, firstLine);
    CUSTOMERCOUNT = std::stoi(firstLine);

    std::vector<std::thread> threadsOfCustomers;                                                                    //  THREADS processing customer affaires.
    
    //Read a new line {CUSTOMERCOUNT} many times and parse required info to construct a new object respectively.                                 
    for(int i=0; i<CUSTOMERCOUNT;i++){
        
        std::string line; getline(ReadFile, line); std::vector<std::string> lineArray = parseStringToArray(line);   //                LINE CONTENT 2x2        
        int sleepDuration=std::stoi(lineArray[0]); int payFromMachineID=std::stoi(lineArray[1]);//                              |sleepDuration|payFromMachineID|
        std::string payToCompany = lineArray[2]; int payAmount=std::stoi(lineArray[3]);//                                       | payToCompany|payAmount       |

        // Create new thread and append to array.
        threadsOfCustomers.push_back(std::thread(createNewCustomerThread, i,0, sleepDuration, payFromMachineID, payToCompany, payAmount));
    };
    //Join threads using void join();
    for(int j=0;j<CUSTOMERCOUNT;j++){
        threadsOfCustomers[j].join();  
    }
 
/*                           --TRANSACTIONS--                                                                        */

/*                            print console                                                                          */    
    for(int i=0;i<COMPANYCOUNT;i++)
        COMPANIES[i] -> toConsole();
        
    return 0;
}

void createNewMachine(int GenerationLoopCounter){
    VendingMachine* mach = new VendingMachine(GenerationLoopCounter);   
    MACHINES[GenerationLoopCounter]=mach;
    //printDetailsOfMachineWithIndex(GenerationLoopCounter);
}
void createNewCustomerThread(int GenerationLoopCounter,int id, int sleepDuration, int payFromMachineID, std::string payToCompany, int payAmount){
    
    Customer* customer = new Customer(sleepDuration, payFromMachineID, payToCompany, payAmount);
    CUSTOMERS[GenerationLoopCounter] = customer;//printDetailsOfCustomerWithIndex(GenerationLoopCounter);
    std::this_thread::sleep_for(std::chrono::milliseconds(customer -> getSleepDuration()));
    customer -> buyTicket();         /*CUT  std::cout << "Customer "      << customer -> getID()               <<" Ready!:" 
                                                      << "goToMachineID(" << customer -> getPayFromMachineID() << ") "
                                                      << "payToCompany("  << customer -> getPayToCompany()     << ") "
                                                      << "payAmount("     << customer -> getPayAmount()        << ") "<< std::endl;
                                    CUT*/
}
void printDetailsOfCustomerWithIndex(int i){
    std::thread::id threadID = std::this_thread::get_id();
    std::cout << "printThreadID:"<< threadID <<" customerDetails:";
    CUSTOMERS[i] -> toConsole();
}
void printDetailsOfMachineWithIndex(int i){
    std::thread::id threadID = std::this_thread::get_id();
    std::cout << "printThreadID: "<< threadID <<" machineDetails : ";
    MACHINES[i] -> toConsole();
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
banks hashit (std::string const& inString) {
    if (inString == "Bob"   ) return bob;
    else if (inString == "Dave"  ) return dave;
    else if (inString == "Kevin" ) return kevin;
    else if (inString == "Otto"  ) return otto;
    else if (inString == "Stuart") return stuart;
    return null;
};
/*  void join();
    .    The function returns when the thread execution has completed.
    .        This synchronizes the moment this function returns with the completion of all the operations in the thread: 
    .        This blocks the execution of the thread that calls this function, 
    .        until the function called on construction returns (if it hasn't yet).                                    */                                        

//"""                             DebugTools                             """;
    /*  
        """//CutAboveLine//""";
            
        for(int i=0;i<COMPANYCOUNT;i++)
            COMPANIES[i] -> toConsole();

        for(int i=0;i<MACHINECOUNT;i++)
            MACHINES[i]-> toConsole();

        for(int i=0;i<CUSTOMERCOUNT;i++)
            CUSTOMERS[i] -> toConsole();
        */
