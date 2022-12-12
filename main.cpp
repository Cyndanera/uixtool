#include <fstream>
#include <iostream>
#include <string>

unsigned long key[16];
unsigned long fileSize = 0;

std::string mode = "";
std::string cfgname = "";
std::string path = "";
std::string outname = "";

char* readFileData(std::string filename);
unsigned long getFileSizeEX(std::string filename);

int main(int argc, char** argv) {
	std::fstream cfgfile;
	std::fstream fileout;

    // init custom uix key
    for (int i = 0; i < fileSize; i += 16)
    {
	    key[i] = 0;
    }

#ifndef _DEBUG
	if (argc < 4) {
		// print usage here and return, since that's what you need.
		std::cout << "uixtool mode cfgfile infile outfile" << std::endl;
	}
	else {
		mode = argv[1];
		cfgname = argv[2];
		path = argv[3];
		outname = argv[4];
	}
#else
	mode = "encrypt";
	cfgname = "uix.xor";
    path = "uix.xml";
	outname = "uix.bin";
#endif

    fileSize = getFileSizeEX(path);
	char* file = readFileData(path);
	
	cfgfile.open(cfgname, std::ios::in);
	if (cfgfile.is_open()) {

		for (int i = 0; i < 16; i++) {
			cfgfile >> key[i];
		}

		cfgfile.close();
	}

	if (mode == "decrypt")
	{
		for (int i = 0; i < fileSize; i += 16) file[i] -= key[0];
		for (int i = 1; i < fileSize; i += 16) file[i] -= key[1];
		for (int i = 2; i < fileSize; i += 16) file[i] -= key[2];
		for (int i = 3; i < fileSize; i += 16) file[i] -= key[3];
		for (int i = 4; i < fileSize; i += 16) file[i] -= key[4];
		for (int i = 5; i < fileSize; i += 16) file[i] -= key[5];
		for (int i = 6; i < fileSize; i += 16) file[i] -= key[6];
		for (int i = 7; i < fileSize; i += 16) file[i] -= key[7];
		for (int i = 8; i < fileSize; i += 16) file[i] -= key[8];
		for (int i = 9; i < fileSize; i += 16) file[i] -= key[9];
		for (int i = 10; i < fileSize; i += 16) file[i] -= key[10];
		for (int i = 11; i < fileSize; i += 16) file[i] -= key[11];
		for (int i = 12; i < fileSize; i += 16) file[i] -= key[12];
		for (int i = 13; i < fileSize; i += 16) file[i] -= key[13];
		for (int i = 14; i < fileSize; i += 16) file[i] -= key[14];
		for (int i = 15; i < fileSize; i += 16) file[i] -= key[15];
	}
	else if (mode == "encrypt")
	{
		for (int i = 0; i < fileSize; i += 16) file[i] += key[0];
		for (int i = 1; i < fileSize; i += 16) file[i] += key[1];
		for (int i = 2; i < fileSize; i += 16) file[i] += key[2];
		for (int i = 3; i < fileSize; i += 16) file[i] += key[3];
		for (int i = 4; i < fileSize; i += 16) file[i] += key[4];
		for (int i = 5; i < fileSize; i += 16) file[i] += key[5];
		for (int i = 6; i < fileSize; i += 16) file[i] += key[6];
		for (int i = 7; i < fileSize; i += 16) file[i] += key[7];
		for (int i = 8; i < fileSize; i += 16) file[i] += key[8];
		for (int i = 9; i < fileSize; i += 16) file[i] += key[9];
		for (int i = 10; i < fileSize; i += 16) file[i] += key[10];
		for (int i = 11; i < fileSize; i += 16) file[i] += key[11];
		for (int i = 12; i < fileSize; i += 16) file[i] += key[12];
		for (int i = 13; i < fileSize; i += 16) file[i] += key[13];
		for (int i = 14; i < fileSize; i += 16) file[i] += key[14];
		for (int i = 15; i < fileSize; i += 16) file[i] += key[15];
	}
	
	fileout.open(outname, std::ios::out | std::ios::binary);
	if (fileout.is_open()) {
		fileout.write(file, fileSize);
		fileout.close();
	}
	
    return 0;
}

char* readFileData(std::string filename)
{
	std::fstream file;
    char* data;
    unsigned long size = getFileSizeEX(filename);
    
    file.open(filename, std::ios::in | std::ios::binary);
    if (file.is_open()) {
		data = new char[size];
		file.read(data, size);
		file.close();
		return data;
	}
	else 
	{
	    return 0;
	}
}

unsigned long getFileSizeEX(std::string filename) {
	unsigned long size = 0;
	std::fstream file;

	file.open(filename, std::ios::in | std::ios::binary);

	if (file.is_open()) {
		file.seekg(0, std::ios::end);
		size = file.tellg();
	}
	else {
		std::cout << "Error - " << filename << "\n";
	}

	return size;
}