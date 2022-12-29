class Customer {
    private:
        int _id;
        int _sleepDuration;
        int _payFromMachineID;
        std::string _payToCompany;   
        int _payAmount;
        customerStatus status;

    public:
        Customer(int id, int sleepDuration, int payFromMachineID, std::string payToCompany, int payAmount);
        void toConsole();
};

/*Customer Constructor*/
Customer::Customer(int id, int sleepDuration, int payFromMachineID, std::string payToCompany, int payAmount){
    _id = id;
    _sleepDuration = sleepDuration;
    _payFromMachineID = payFromMachineID;
    _payToCompany = payToCompany;
    _payAmount = payAmount;
    status = created;
}

void Customer::toConsole(){
    std::cout << "Customer " << _id  << ": [" << _sleepDuration << ","<< _payFromMachineID << ","<< _payToCompany << ","<< _payAmount << ","<< status << "]"<< std::endl;
}