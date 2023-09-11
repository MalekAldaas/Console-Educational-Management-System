#include "../Headers/helper_func.h"
#include "../Headers/account.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<std::string> readLine(std::string line)
{
    std::vector<std::string> splitedLine;
    std::string tem = "";
    for (int i = 0; i < (int)line.size(); i++)
    {
        if (line[i] == ',')
        {
            splitedLine.push_back(tem);
            tem = "";
        }
        else
            tem += line[i];
    }
    return splitedLine;
}

bool isNumber(const std::string &number)
{
    if ((int)number.size() == 0)
        return false;
    if (number[0] == '0')
        return false;
    for (int i = 0; i < (int)number.size(); i++)
    {
        if (!('0' <= number[i] && number[i] <= '9'))
            return false;
    }
    return true;
}

void appendOnFile(std::string filePath, std::vector<std::string> &details)
{
    std::ofstream outFile(filePath, std::ios::app);
    if (outFile.fail())
    {
        std::cerr << "Error Appending On File, System Faild!." << std::endl;
        return;
    }
    for (std::string tem : details)
        outFile << tem << ",";
    outFile << std::endl;
    outFile.close();
}

void writeOnFile(std::string filePath, std::vector<std::string> &details)
{
    std::ofstream outFile(filePath);
    if (outFile.fail())
    {
        std::cerr << "Error Writing On File,System Faild!.";
        return;
    }
    for (std::string tem : details)
    {
        outFile << tem << std::endl;
    }
    outFile.close();
}

void deleteFromFile(std::string filePath, std::string &stringToDelete)
{
    std::vector<std::string> hold;
    std::string line;
    std::fstream inFile(filePath);
    if (inFile.fail())
    {
        std::cerr << "Error Deleting From File, System Faild!" << std::endl;
        return;
    }
    while (getline(inFile, line))
    {
        if (line == stringToDelete)
            continue;
        hold.push_back(line);
    }
    inFile.close();
    writeOnFile(filePath, hold);
}
bool vectorExistInFile(std::string filePath, std::vector<std::string> &data)
{
    std::ifstream File(filePath);
    if (File.fail())
    {
        std::cerr << "Error Checking File, System Faild!" << std::endl;
        return false;
    }
    std::string line;
    bool found = false;
    while (getline(File, line))
    {
        std::vector<std::string> tem = readLine(line);
        if (tem == data)
        {
            found = true;
            break;
        }
    }
    File.close();
    return found;
}

void input_username(std::string &_username)
{
    std::cout << "Input username: ";
    getline(std::cin, _username);
}

void input_password(std::string &_password)
{
    std::cout << "Input password: ";
    getline(std::cin, _password);
}

void input_name(std::string &_name)
{
    std::cout << "Input name: ";
    getline(std::cin, _name);
}

void input_email(std::string &_email)
{
    std::cout << "Input email: ";
    getline(std::cin, _email);
}

void input_age(std::string &_age)
{
    std::cout << "Input age: ";
    getline(std::cin, _age);
}

void input_accountType(std::string &_accountType)
{
    std::cout << "Input your account type :" << std::endl;
    std::cout << "1 for Student, 2 for Doctor, 3 for Teacher Assistant, ";
    input_number(_accountType, {1, 3});
    if (_accountType == "1")
        _accountType = "Student";
    else if (_accountType == "2")
        _accountType = "Doctor";
    else if (_accountType == "3")
        _accountType = "Teacher Assistant";
}

bool input_number(std::string &number, std::pair<int, int> range)
{
    std::cout << "Input number in range " << range.first << "-" << range.second << ": ";
    getline(std::cin, number);
    if (isNumber(number))
    {
        int x = std::stoi(number);
        if (range.first <= x && x <= range.second)
            return true;
    }
    std::cout << "Invalid Input." << std::endl;
    return false;
}
std::string putOnString(std::vector<std::string> &data){
    std::string result = "" ;
    for(int i = 0; i < (int)data.size(); i++){
        result  +=  data[i];
        result  +=  "," ;
    }
    return result ;
}