#pragma once

#include "pugixml.hpp"
#include <fstream>
#include <string>

class FileHandling //TODO: implement XML file handling
{

public:
	FileHandling();
	~FileHandling();

	void xmlLoad(std::string file_name);
	void xmlSave(std::string file_name);

	//Read From File - Calls a function to create a default file if file not found
	std::string ReadFF(std::string file_name, std::string identifier); 
	std::string ReadToEnd(std::string file_name, std::string identifier);
	//Write To File - Creates file if non-existant
	void Write2F(std::string name, std::string datastream); 

private:
	//File Exists
	bool FExists(); 

	pugi::xml_document doc_;
	std::ifstream read_;
	std::ofstream write_;
	std::string file_name_;
	std::string data_;
};