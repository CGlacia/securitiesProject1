/*	Jade Knoll - Computer Security
	Project 1 - RC4
	13 November 2017
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
This command-line program takes in a .txt file as input and outputs to another .txt file. It can
encrypt or decrypt according to RC4.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "RC4.h"
using namespace std;

int State[256];
int i, j;

bool EncryptDecrypt(string key, string inputFile, string outputFile)
{
	//initialize/scramble the State

	for (i = 0; i <= 255; i++)
	{
		State[i] = i;
	}

	i = j = 0;
	int length = key.length();

	for (i = 0; i <= 255; i++)
	{
		j = (j + State[i] + (char)key[i % length]) % 256;

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
	bool completedWithoutErrors = false;

	if (output.is_open() && input.is_open())
	{
		char fromInput, toOutput;
		unsigned char fromState;

		input.get(fromInput);

		while (!input.eof())
		{
			fromState = GetStateByte();
			toOutput = fromInput ^ fromState;

			if (outputFile == "output.txt")
				printf("%x", toOutput);
			else
				output << toOutput;

			input.get(fromInput);
		}

		cout << "Encryption/Decryption completed!";
		completedWithoutErrors = true;
	}
	else if(!output.is_open())
	{
		cout << "The output file couldn't be opened." << endl;
	}
	else if (!input.is_open())
	{
		cout << "The input file couldn't be opened." << endl;
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

string convertHexToAscii(string hex)
{
	string ascii = "";
	int length = hex.length();

	if (length % 2 != 0)
	{
		cout << "This hex input contains an odd number of hex digits.\n" << 
				"Please adjust your input and try again." << endl;
		return "";
	}

	for (int k = 0; k < length; k += 2)
	{
		string hexbyte = hex.substr(k, 2);

		if (hexbyte.find_first_not_of("0123456789abcdefABCDEF", 2) != string::npos)
		{
			cout << "An invalid character for hexadecimal-formatted input was found.\n" << 
					"Please adjust your input and try again." << endl;
			return "";
		}

		char c = (int)strtol(hexbyte.c_str(), NULL, 16);
		ascii.push_back(c);
	}

	return ascii;
}

int main(int argc, char* argv[])
{
	string key = "", infile = "", outfile = "";

	cout << "  Welcome to the RC4 encryptor!\n" <<
			"  Provide a key up to 256 characters in length, the name of an input\n" <<
			"  file, and the name of an output file. If you'd like to use standard\n" <<
			"  I/O instead of a file for either end, pass a - (hyphen) in place of\n" <<
			"  a file name. Keys composed of ASCII characters must be enclosed in\n" <<
			"  single quotes; if the key includes spaces, enclose in both double\n" <<
			"  and single quotes, like \"'this'\". They may also be hexadecimal,\n" <<
			"  and should not be enclosed in quotes of any kind. (No spaces allowed\n" <<
			"  in hex input.) Happy encrypting/decrypting!\n\n" <<
			"Proper usage: " << argv[0] << " <key> <name of input file> <name of output file>" << endl;

	if (argc != 4)
	{
		cout << "Exactly four arguments (that's the program name, key, input file, and \n" << 
				"output file) are required for this program." << endl;
		return 1;
	}

	key = argv[1];
	int keyLen = key.length();

	if (key[0] != '\'' && key[keyLen - 1] != '\'') //it's a hex key
	{
		if (keyLen > 512)
		{
			cout << "This hex key is longer than 512 characters.\n" << 
					"Please trim it down and try again." << endl;
			return 1;
		}

		key = convertHexToAscii(key);

		if (key.empty())
			return 1;

		cout << "hexkey = " << key << endl;
	}
	else
	{
		if (keyLen > 256)
		{
			cout << "This ASCII key is longer than 256 characters.\n" << 
					"Please trim it down and try again." << endl;
			return 1;
		}

		key = (string)key.substr(1, keyLen - 2);
	}

	if (argv[2] == "-") //std input
	{
		string plaintext = "";
		infile = "input.txt";

		cout << "Enter the text you want to encrypt in hex form.\n" << endl;
		cin >> plaintext;
		plaintext = convertHexToAscii(plaintext);

		ofstream toInputFile; //instead of writing another method, going to write the input to in.txt
		toInputFile.open(infile.c_str(), ios::out | ios::binary);

		if (toInputFile.is_open())
			toInputFile << plaintext;

		toInputFile.close();
	}
	else
	{
		infile = argv[2];
	}

	if (argv[3] == "-")
	{
		outfile = "out.txt";
	}
	else
	{
		outfile = argv[3];
	}
	
	if(argv[2] == argv[3] && !(argv[2] == "-" && argv[3] == "-")) //same file name for both input and output
	{
		cout << "You can't use the same file for both the input and output." << endl;
		return 1;
	}

	EncryptDecrypt(key, infile, outfile);

	return 0;
}