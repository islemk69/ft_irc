#include "../includes/Channel.hpp"

Channel::Channel(const std::string name):_name(name){}
Channel::~Channel(){}
std::string     Channel::getName() const{
    return this->_name;
}