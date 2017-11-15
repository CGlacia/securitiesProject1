// RC4Analysis.cpp : Defines the entry point for the console application.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct gram
{
	string text;
	int count;
} grm;

vector<gram> grams;

int main()
{
	string filename = "", outFile = "analysis.txt";
	int type = 0;

	cout << "Enter the name of the file you want examined." << endl;
	cin >> filename;
	cout << "Single-character (1), or digram (2) analysis?" << endl;
	cin >> type;

	if (type == 1) //single character analysis
	{
		fstream input;
		input.open(filename.c_str(), ios::in | ios::binary);

		char firstch;
		bool foundGram = false, needSecond = true;

		if (input.is_open())
		{
			input.get(firstch);

			while (!input.eof())
			{
				int gSize = grams.size();

				for (int i = 0; i < gSize; i++)
				{
					if (grams[i].text == string(1, firstch))
					{
						grams[i].count = grams[i].count + 1;
						foundGram = true;
						break;
					}
				}

				if (!foundGram)
				{
					gram newGram;
					newGram.text = string(1, firstch);
					newGram.count = 1;
					grams.push_back(newGram);
				}

				foundGram = false;
				input.get(firstch);
			}
		}
		else
		{
			cout << "Input couldn't be opened." << endl;
			return 1;
		}

		input.close();
	}
	else if (type == 2)
	{
		fstream input;
		input.open(filename.c_str(), ios::in | ios::binary);

		char firstch, seconch;
		bool foundGram = false, needSecond = true;

		if (input.is_open())
		{
			input.get(firstch);

			while (!input.eof())
			{
				input.get(seconch);
				string thisGram = string(1, firstch) + string(1, seconch);
				int gSize = grams.size();

				for (int i = 0; i < gSize; i++)
				{
					if (grams[i].text == thisGram)
					{
						grams[i].count = grams[i].count + 1;
						foundGram = true;
						break;
					}
				}

				if (!foundGram)
				{
					gram newGram;
					newGram.text = thisGram;
					newGram.count = 1;
					grams.push_back(newGram);
				}

				foundGram = false;
				firstch = seconch;
			}
		}
		else
		{
			cout << "Input couldn't be opened." << endl;
			return 1;
		}

		input.close();
	}

	ofstream output;
	output.open(outFile.c_str(), ios::out | ios::binary);

	if (output.is_open())
	{
		output << "gram\tcount\n";

		for (gram g : grams)
		{
			output << g.text << "\t" << g.count << "\n";
		}
	}
	else
	{
		cout << "analysis.txt couldn't be found." << endl;
	}

	output.close();

	cout << "Analysis complete! Check analysis.txt." << endl;

    return 0;
}