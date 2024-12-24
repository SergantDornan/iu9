#include <iostream>
#include <string>
#include <fstream>
#include <vector>
int find(std::vector<std::string>& v,const std::string s){
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == s)
			return i;
	}
	return -1;
}
void findAll(const std::string path, std::vector<std::string>& includes,
	std::vector<std::string>& incFiles){
	std::string line;
	std::ifstream in(path);
	while(std::getline(in, line)){
		if(line.find("#include") != std::string::npos){
			std::string file(line.begin() + line.find("#include") + 10, line.end()-1);
			std::ifstream incFile(file);
			if(incFile.is_open()){
				if(find(incFiles, file) == -1){
					findAll(file,includes,incFiles);
					incFiles.push_back(file);
				}
			}
			else{
				if(find(includes, line) == -1)
					includes.push_back(line);
			}
			incFile.close();
		}
		else
			break;
	}
	in.close();
}
int main(int argc, char* argv[]){
	system("rm main");
	std::vector<std::string> includes;
	std::vector<std::string> incFiles;
	std::vector<std::string> lines;
	findAll("main.c",includes,incFiles);
	for(int i = 0; i < includes.size(); ++i)
		lines.push_back(includes[i]);
	for(int i = 0; i < incFiles.size(); ++i){
		std::ifstream in(incFiles[i]);
		std::string line;
		while(std::getline(in,line)){
			if(line.find("#include") == std::string::npos)
				lines.push_back(line);
		}
		in.close();
	}
	std::ifstream in("main.c");
	std::string line;
	while(std::getline(in,line)){
		if(line.find("#include") == std::string::npos)
			lines.push_back(line);
	}
	in.close();

	std::ofstream out("code.c");
	for(int i = 0; i < lines.size(); ++i)
		out << lines[i] << std::endl;
	out.close();
	system("gcc code.c -o main");
	std::ifstream comp("main");
	if(comp.is_open()){
		std::cout << "======= SUCCES ======" << std::endl;
	}
	comp.close();
	return 0;
}