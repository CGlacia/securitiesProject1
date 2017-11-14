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
int i, j;

bool EncryptDecrypt(string key, string inputFile, string outputFile)
{
	//initialize/scramble the State

	for (i = 0; i <= 255; i++)
	{
		State[i] = i;
	}

	i = j = 0;

	for (i = 0; i <= 255; i++)
	{
		j = (j + State[i] + (char)key[i % key.length()]) % 256;

		int temp = State[i];
		State[i] = State[j];
		State[j] = temp;
	}

	i = j = 0;

	//xor the State with the input

	fstream input;
	ofstream output;
	input.open(inputFile.c_str(), ios::in | ios::binary);
	output.open(outputFile.c_str(), ios::out | ios::binary);
	bool completedWithoutErrors = true;

	if (output.is_open() && input.is_open())
	{
		char fromInput, toOutput;
		unsigned char fromState;

		input.get(fromInput);

		while (!input.eof())
		{
			fromState = GetStateByte();
			toOutput = fromInput ^ fromState;

			if (outputFile == "out.txt")
				cout << toOutput;
			else
				output << toOutput;

			input.get(fromInput);
		}

		cout << "Encryption/Decryption completed!";
	}
	else if(!output.is_open())
	{
		cout << "The output file couldn't be opened." << endl;
		completedWithoutErrors = false;
	}
	else if (!input.is_open())
	{
		cout << "The input file couldn't be opened." << endl;
		completedWithoutErrors = false;
	}

	input.close();
	output.close();

	return completedWithoutErrors;
}

unsigned char GetStateByte()
{
	i = (i + 1) % 256;
	j = (j + State[i]) % 256;

	int temp = State[i];
	State[i] = State[j];
	State[j] = temp;

	return (char)State[(State[i] + State[j]) % 256];
}

int main(int argc, char* argv[])
{
	string key = "", infile = "", outfile = "";

	cout << "  Welcome to the RC4 encryptor!\n" <<
			"  Provide a key up to 256 characters in length, the name of an input\n" <<
			"  file, and the name of an output file. If you'd like to use standard\n" <<
			"  I/O instead of a file for either end, pass a - (hyphen) in place of a\n" <<
			"  file name. Keys composed of ASCII characters must be enclosed in\n" <<
			"  single quotes; if the key includes spaces, enclose in both double and\n" <<
			"  single quotes, like \"'this'\". They may also be hexadecimal, and\n" <<
			"  should not be enclosed in quotes of any kind. \n" <<
			"  Happy encrypting/decrypting!\n\n" <<
			"Proper usage: " << argv[0] << " <key> <name of input file> <name of output file>" << endl;

	if (argc != 4)
	{          //1234567890123456789012345678901234567890123456789012345678901234567890
		cout << "Exactly four arguments (that's the program name, key, input file, and \n" << 
				"output file) are required for this program." << endl;
		return 1;
	}

	key = argv[1];

	if (key[0] != '\'' && key[key.length() - 1] != '\'') //it's a hex key
	{

	}
	else
	{
		key = (string)key.substr(1, key.length()-1);
	}

	if (argv[2] == "-") //std input
	{
		string plaintext = "";
		infile = "in.txt";

		cout << "Enter the text you want to encrypt.\n" << endl;
		cin >> plaintext;

		ofstream toInputFile; //instead of writing another method, going to write the input to in.txt
		toInputFile.open(infile.c_str(), ios::out | ios::binary);

		if (toInputFile.is_open())
			toInputFile << plaintext;

		toInputFile.close();
	}
	else
		infile = argv[2];

	if (argv[3] == "-")
		outfile = "out.txt";
	else
		outfile = argv[3];
	
	if(argv[2] == argv[3] && !(argv[2] == "-" && argv[3] == "-")) //same file name for both input and output
	{
		cout << "Hold on. You can't use the same file for both the input and output." << endl;
		return 1;
	}

	EncryptDecrypt(key, infile, outfile);

	return 0;
}