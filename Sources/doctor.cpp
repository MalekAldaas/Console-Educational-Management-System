#include"../Headers/account.h"
#include"../Headers/doctor.h"

#include<string>
#include<vector>

Doctor::Doctor(){
    this->account.initialize() ;
}
Doctor::Doctor(const Account& account){
    
}