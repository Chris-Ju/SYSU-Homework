#include "player.hpp"
#include <iostream>
#include <string>
char * abc(int n);
Player::Player()
{
	this->m_role = Uninitialized;
  this->m_name = "";
}

void Player::init(std::string name, Role role)
{
	this->m_name = name;
	m_role = role;
}

Player::Role Player::role() const
{
	return this->m_role;
}

void Player::answer() const
{
	std::cout << m_name << ": Shh... I am a "<< abc(this->m_role) << "." << std::endl;
}
void Player::pretend() const
{
	std::cout << m_name << ": I am the villager!!" << std::endl;
}
Player::~Player()
{
	this->m_name = "";
}

char *abc(int n)
{
  switch(n)
   {
       case 1:return "Villager";
       case 2:return "Werewolf";
       case 3:return "Seer";
       case 4:return "Witch";
       case 5:return "Hunter";
         default:return "";
   }
  
}
