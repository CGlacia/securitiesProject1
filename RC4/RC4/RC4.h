#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool EncryptDecrypt(string, string, string);
unsigned char GetStateByte();
string convertHexToAscii(string);