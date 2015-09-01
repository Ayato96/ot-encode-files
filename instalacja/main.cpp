#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <dirent.h>
#include <windows.h>

#define READ_SPR_SIZE (5 * 1024)

using namespace std;

template <typename T>
T read(std::ifstream* file, char* memblock, uint32_t pos)
{
	file->seekg(pos);
	file->read(memblock, sizeof(T));
	return *(T*)(memblock);
}

template <typename T>
void write(std::ofstream* file, const T& v)
{
	file->write((char*)&v, sizeof(T));
}

bool EncodeSpr(std::string oldFileName, std::string newFileName)
{
	//Read
	std::ifstream file(oldFileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if(!file.is_open())
	{
		std::cout << ">> Unable to open file: " << oldFileName << std::endl;
		system("PAUSE");
		return EXIT_SUCCESS;
	}

	ifstream::pos_type size = file.tellg();
	char memblock[READ_SPR_SIZE + 0xFF];
	file.seekg(0, std::ios::beg);


	//Write
	std::ofstream newFile(newFileName.c_str(), std::ios::out | std::ios::binary | std::ios::ate);
	if(!newFile.is_open())
	{
		std::cout << ">> Unable to open file: " << newFileName << std::endl;
		system("PAUSE");
		return EXIT_SUCCESS;
	}

	for(int64_t i = 0; i < size; (i += READ_SPR_SIZE))
	{
		file.seekg(i);
		file.read(memblock, READ_SPR_SIZE);
		
		for(int64_t x = 0; x < std::min(READ_SPR_SIZE, (int32_t)(size - i)); x++)
			memblock[x] = memblock[x] ^ 5;
		
		newFile.write(memblock, std::min(READ_SPR_SIZE, (int32_t)(size - i)));
	}

	file.close();
	newFile.close();
}

bool EncodeFile(std::string oldFileName, std::string newFileName)
{
	//Read
	std::ifstream file(oldFileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if(!file.is_open())
	{
		std::cout << ">> Unable to open file: " << oldFileName << std::endl;
		system("PAUSE");
		return EXIT_SUCCESS;
	}

	ifstream::pos_type size = file.tellg();
	char* memblock = new char[size];
	file.seekg(0, std::ios::beg);
	file.read(memblock, size);
	file.close();


	//Write
	std::ofstream newFile(newFileName.c_str(), std::ios::out | std::ios::binary | std::ios::ate);
	if(!newFile.is_open())
	{
		std::cout << ">> Unable to open file: " << newFileName << std::endl;
		system("PAUSE");
		return EXIT_SUCCESS;
	}

    int32_t key = 0;
    int32_t keys[10] = {96, 8, 25, 18, 148, 30, 68, 205, 9, 168};

	for(int32_t i = 0; i < size; i++)
	{
		newFile << (uint8_t)(memblock[i] ^ keys[key]);

		if((++key) >= 9)
			key = 0;
	}

	newFile.close();
	delete memblock;
}

void getFilesFromDir(const std::string& path, std::vector<std::string>& files, std::string fileType)
{
	std::vector<std::string> vec;
	DIR *dir;
	struct dirent *ent;

	if((dir = opendir(path.c_str())))
	{
		while((ent = readdir(dir)))
		{
			std::string s = std::string(ent->d_name);
			if(s.substr(s.find_last_of(".") + 1) == fileType)
				files.push_back(path + "/" + s);
			else if(s != "." && s != "..")
				getFilesFromDir(path + "/" + s, files, fileType);
		}

		closedir(dir);
	}
}

int32_t main()
{    
	std::vector<std::string> files;
	getFilesFromDir("data", files, "lua");
	getFilesFromDir("data", files, "png");
	getFilesFromDir("data", files, "otps");
	getFilesFromDir("data", files, "otfont");
	getFilesFromDir("data", files, "otml");
	getFilesFromDir("data", files, "otui");
	getFilesFromDir("data", files, "otmod");

	std::cout << "> Founded files: " << files.size() << std::endl;

	for(std::vector<std::string>::iterator name = files.begin(); name != files.end(); name++)
		EncodeFile(*name, "new "+ (*name));


	// let's find spr
	files.clear();
	getFilesFromDir("data", files, "spr");
	std::cout << "> Founded sprites: " << files.size() << std::endl;
	for(std::vector<std::string>::iterator name = files.begin(); name != files.end(); name++)
		EncodeSpr(*name, "new "+ (*name));

	std::cout << "> Done" << std::endl;
	return EXIT_SUCCESS;
}
