#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

std::vector<std::string> readLine(std::string) ;
void appendOnFile(const std::string&, const std::vector<std::string>&) ;
void writeOnFile(const std::string&, const std::vector<std::string>&) ;

bool isNumber(const std::string&) ;

void input_username(std::string&);
void input_password(std::string&);
void input_email(std::string&) ;
void input_name(std::string&) ;
void input_age(std::string&) ;
void input_accountType(std::string&) ;
bool input_number(std::string&, const std::pair<int,int>&) ;

#endif