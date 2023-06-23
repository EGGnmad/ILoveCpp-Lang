#include <fstream>
#include <iostream>

#include "ILoveCpp.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace std;
using namespace ilovecpp;

int main(int argc, char* argv[])
{
    string basicTemplateStart = "#include <iostream>\n#include <string>\nusing namespace std;\nint main(){\n";
    string basicTemplateEnd = "return 0;\n}";


    string outputPath = "a.cpp";
	string filePath = argv[1];

    string input;

	// read File
	ifstream openFile(filePath.data());
	if( openFile.is_open() ){
		string in;
		while(getline(openFile, in)){
			cout << in << endl;
			input += in;
		}
		openFile.close();
	}

	// write File
	ofstream writeFile(outputPath.data());
	if( writeFile.is_open() ){
        Lexer lexer = Lexer(input);
        Parser parser = Parser(&lexer);

        ProgramStatement output = parser.ParseProgram();

        writeFile << basicTemplateStart;
        writeFile << output.ToString();
        writeFile << basicTemplateEnd;

		writeFile.close();
	}

	return 0;
}