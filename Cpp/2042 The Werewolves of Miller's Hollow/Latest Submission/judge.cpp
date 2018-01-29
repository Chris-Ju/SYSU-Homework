  #include "judge.hpp"
#include "player.hpp"
#include <iostream>
#include <string>
char * abcd(int n);
Judge::Judge()
{
	this->m_players_count = 0;
}

Judge::~Judge()
{
  int i;
		for(i = 0;i < this->kMaxCountOfPlayers; i++)
  {
     (this->m_players[i])->~Player();
   }
}

void Judge::on(const Player* player)
{
	this->m_players[this->m_players_count++] = player;
}

void Judge::call(Player::Role role)
{
	int i;
 std::cout << "Calling: " << abcd(role) << std::endl;
	for(i = 0;i < this->kMaxCountOfPlayers; i++)
	{
  if(role == 1)
	  	m_players[i]->pretend();
		else if(this->m_players[i]->role() == role)
			this->m_players[i]->answer();
	}
}

char *abcd(int n)
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

