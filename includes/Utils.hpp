#ifndef UTILS_HPP
# define UTILS_HPP
# include <vector>
# include <iostream>

//take the string iterate over it find each occurence of the delim and split the string into a vector of string
std::vector<std::string> split(const std::string & msg, const std::string & delim);

#endif