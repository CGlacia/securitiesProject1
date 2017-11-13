/*	Jade Knoll - Computer Security
	Project 1 - RC4
	9 November 2017
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
This command-line program takes in a .txt file as input and outputs to another .txt file. It can
encrypt or decrypt according to RC4.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "RC4.h"

using namespace std;
int State[256];
vector<string> inputHolder;

void EncryptDecrypt(string key, string inputFile, string outputFile)
{
	//read in the input
	input(inputFile);

	//initialize/scramble the State

	for (int i = 0; i <= 255; i++)
	{
		State[i] = i;
	}

	int j = 0;

	for (int i = 0; i <= 255; i++)
	{
		j = (j + State[i] + (char)key[i % key.length()]) % 256;

		int temp = State[i];
		State[i] = State[j];
		State[j] = temp;
	}

	//xor the State with the input

	ofstream output;	// file output time
	output.open(outputFile);

	for (vector<string>::iterator i = inputHolder.begin(); i != inputHolder.end(); ++i)
	{
		string currLine = *i;

		for (char c : currLine)
		{
			if (output.is_open())
			{
				output << (GetStateByte() ^ c);
			}
		}
	}

	output.close();
}

char GetStateByte()
{
	int i = 0, j = 0;

	i = i + 1 % 256;
	j = (j + State[i]) % 256;

	int temp = State[i];
	State[i] = State[j];
	State[j] = temp;

	return (char)State[(State[i] + State[j]) % 256];
}

void input(string filename)
{
	/*	This input method grabs the statements from the input file, input.txt. It uses a
		while loop to read the file until it reaches the end, retrieving the file line
		by line and storing each line into a vector of strings. */

	string line = ""; //a line of text from the input file
	ifstream read(filename);

	if (read.is_open())
	{
		while (!read.eof())
		{
			getline(read, line);
			inputHolder.push_back(line);
			line = ""; //empty line so it's ready for the next one
		}
		read.close();
	}
	else cout << "File can't be opened.";
}

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		cout << "Welcome to the RC4 encryptor! Provide a key up to 256 characters in length, the full name of an\n" <<
			"input file, and the full name of an output file. Keys composed of ASCII characters must be enclosed\n" <<
			"in single quotes; if the key includes spaces, enclose in both double and single quotes, like\n" <<
			"\"'this'\". They may also be hexadecimal, and should not be enclosed in quotes of any kind.\n" <<
			"Happy encrypting/decrypting!\n\n" <<
			"Proper usage: " << argv[0] << " <key> <name of input file> <name of output file>";

		return 1;
	}

	EncryptDecrypt(argv[1], argv[2], argv[3]);

	return 0;
}