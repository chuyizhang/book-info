#ifndef OPERATE_H
#define OPERATE_H
#include <iostream>
#include <cctype>
#include <ctime>
#include <cmath>
#include <vector>
#include "Book.h"
#define TRY_AGAIN 1
int insert(Book);
int delete_record(std::string);
int order(int, int);
int search(std::string, std::vector<std::string>&);
int filter(std::string, std::vector<std::string>);
int select(std::string);
int update_book(std::string, std::vector<std::string>);
std::string format(std::string);
#endif
