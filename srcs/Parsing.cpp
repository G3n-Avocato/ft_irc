#include "Server.hpp"


std::vector<std::string> string_to_vector(std::string str, std::string arg){
    std::vector<std::string>    str_vector;
	std::string                 token;
	size_t                      pos = 0;

    while (str.length() > 0) {
        if((pos = str.find(arg.c_str())) == std::string::npos){
            pos = str.length();
        }
   	    token = str.substr(0, pos);
        str_vector.push_back(token);
        // std::cout << YELLOW << "Server receive CMD: " << RESET << token << std::endl;
        str.erase(0, pos + arg.length());
    }
    return (str_vector);
}

std::vector<std::vector<std::string>> Server::cmdParser(std::string buf){
    std::vector<std::string>                raw_cmd;
    std::vector<std::vector<std::string>>   cmd_vector;

    raw_cmd = string_to_vector(buf, "\r\n");
    int raw_cmd_size = raw_cmd.size();
    int i = 0;
    std::vector<std::string>::iterator it = raw_cmd.begin();
    while (i < raw_cmd_size){
        cmd_vector.push_back(string_to_vector(*it, " "));
        it++;
        i++;
    }
    
    return (cmd_vector);
}