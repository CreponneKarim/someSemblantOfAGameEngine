#ifndef COMMON_USED_FUNCTION_CPP
#define COMMON_USED_FUNCTION_CPP
#include <include/someSemblantOfAGameEngine/CommonUsedFunctions.hpp>


std::vector<std::string>* stringFunctions::split(std::string str,char delimiter){
	if(str!=""){
		std::vector<std::string> *vec = new std::vector<std::string>;
		std::stringstream ss(str);	
		std::string item;
		while(std::getline(ss,item,delimiter)){	
			vec->push_back(item);
		}
		return vec;
	}else{
		return nullptr;
	}
}
#endif