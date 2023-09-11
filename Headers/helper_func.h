#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> readLine(std::string);
void appendOnFile(std::string, std::vector<std::string> &);
void writeOnFile(std::string, std::vector<std::string> &);
void deleteFromFile(std::string, std::string &);
bool vectorExistInFile(std::string, std::vector<std::string> &);

bool isNumber(const std::string &);

void input_username(std::string &);
void input_password(std::string &);
void input_email(std::string &);
void input_name(std::string &);
void input_age(std::string &);
void input_accountType(std::string &);
bool input_number(std::string &, std::pair<int, int>);

std::string putOnString(std::vector<std::string> &);

#endif