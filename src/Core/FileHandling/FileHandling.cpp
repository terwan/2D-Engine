#include "FileHandling.h"

FileHandling::FileHandling()
{
	file_name_ = "";
}


FileHandling::~FileHandling()
{
}

bool FileHandling::FExists()
{
	if (!read_.is_open()) {
		return false;
	}

	return true;
}

void FileHandling::xmlLoad(std::string file_name)
{
	pugi::xml_parse_result result = doc_.load_file(file_name.c_str());
}

void FileHandling::xmlSave(std::string file_name)
{
	doc_.save_file("save_file_output.xml");
}


void FileHandling::Write2F(std::string name, std::string datastream)
{
	file_name_ = name;
	write_.open(file_name_, std::fstream::app);

	write_ << std::endl << datastream << std::endl;

	write_.close();
}

std::string FileHandling::ReadFF(std::string file_name, std::string identifier)
{
	file_name_ = file_name;
	read_.open(file_name_);

	std::string data;

	//Check if file exists;
	if (!FExists()) {
		return data;
	}

	//Extract data from file
	while (!read_.eof()) {

		char comment = read_.peek();

		//Reset error flags if flag is raised
		if (read_.fail() || read_.bad()) {
			read_.clear(); 
		}

		//Ignore Comments  - Lines which begin with #
		if (comment == '#' || comment == '\n') {
			read_.ignore(999, '\n');
			continue;
		}

		//Read in data and store what value is in identifier. Where value come from the file as [NAME] = [VALUE], omitting '=' and whitespace. 
		read_ >> data;

		//If ID is found, read data after it
		if (data.find(identifier) != std::string::npos) {
			read_ >> data;

			// Data is '=' read again
			if (data.find('=') != std::string::npos) read_ >> data;

			read_.close();
			return data;
		}
	}

	read_.close();
	return data;
}

std::string FileHandling::ReadToEnd(std::string file_name, std::string identifier)
{
	file_name_ = file_name;
	read_.open(file_name_);

	std::string data;

	//Check if file exists; If it doesn't, return the empty data string
	if (!FExists()) {
		return data;
	}

	//Keep searching through file until the identifier to start the read is found
	while (!read_.eof()) {
		read_ >> data;
		if (data.find(identifier) != std::string::npos) {
			data.clear();
			break;
		}
	}

	//Build data string with every character in the file 
	//from the read position to the end
	while (!read_.eof()) {
		char ch;
		read_.get(ch);
		
		//Discarge non printable characters
		if (ch <= 32) continue;

		//add character to string
		data.push_back(ch);
	}

	//Close file and return data
	read_.close();
	return data;
}