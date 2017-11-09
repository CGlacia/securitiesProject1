/*	Jade Knoll - Computer Security
	Project 1 - RC4
	9 November 2017
	1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
	This command-line program takes in a .txt file as input and outputs to another .txt file. It can
	encrypt or decrypt according to RC4. 
*/

#include <iostream>
#include <fstream>

using namespace std;
int[] State = new int[256];

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Welcome to the RC4 encryptor! Provide a key up to 256 characters in length, the full name of an \n" + 
				"input file, and the full name of an output file. Keys composed of ASCII characters must be enclosed \n" + 
				"in single quotes; if the key includes spaces, enclose in both double and single quotes, like \n" +
				"\"'this'\". They may also be hexadecimal, and should not be enclosed in quotes of any kind. \n" +
				"Happy encrypting/decrypting! \n\n" +
				"Proper usage: " argv[0] << " <key> <name of input file> <name of output file>";
		
		return 1;
	}
	
	EncryptDecrypt(argv[1], argv[2], argv[3]);
	
	return 0;
}

void EncryptDecrypt(String key, String inputFile, String outputFile)
{
	for(int i = 0; i <= 255; i++)
	{
		State[i] = i;
	}
	
	int j = 0;
	
	for(int i = 0; i <= 255; i++)
	{
		j = (j + State[i] + key[i % key.length()]) % 256
		
		int temp = State[i];
		State[i] = S[j];
		State[j] = temp;
	}
	
	
	
}

byte GetStateByte()
{
	int i = j = 0;
	
	i = i + 1 % 256;
	j = (j + State[i]) % 256;
	
	int temp = State[i];
	State[i] = S[j];
	State[j] = temp;
	
	return State[(State[i] + State[j]) % 256];
}