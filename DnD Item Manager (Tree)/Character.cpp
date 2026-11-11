#include "Character.h"
#include <iostream>
#include <cstring>

Character::Character()
{
	strncpy(m_sName, "Bob", 64);
	m_sName[64] = '\0';
	m_iClass = 1;
	m_iAlignment = 1;
	m_iHitPoints = 1;
	m_iCharTraits[0] = 1;
	m_iCharTraits[1] = 1;
	m_iCharTraits[2] = 1;
	m_iCharTraits[3] = 1;
	m_iCharTraits[4] = 1;
	m_iCharTraits[5] = 1;

	m_pNext = NULL;

	BattleItems = new Possessions();
	TreasureItems = new Possessions();
}

Character::Character(char* name, int clas, int alignment, int hitpoints, int strength,
	int dexterity, int constitution, int intelligence, int wisdom,
	int charisma)
{
	strncpy(m_sName, name, 64);
	m_sName[64] = '\0';

	m_iClass = clas;
	m_iAlignment = alignment;
	m_iHitPoints = hitpoints;
	m_iCharTraits[0] = strength;
	m_iCharTraits[1] = dexterity;
	m_iCharTraits[2] = constitution;
	m_iCharTraits[3] = intelligence;
	m_iCharTraits[4] = wisdom;
	m_iCharTraits[5] = charisma;

	m_pNext = NULL;

	BattleItems = new Possessions();
	TreasureItems = new Possessions();
}

Character::~Character()
{
	delete BattleItems;
	delete TreasureItems;
}

char* Character::getName()
{
	return m_sName;
}

void Character::setName(char* name)
{
	strncpy(m_sName, name, 64);
	m_sName[64] = '\0';
}

int Character::getClass()
{
	return m_iClass;
}

void Character::setClass(int cl)
{
	m_iClass = cl;
}

int Character::getAlignment()
{
	return m_iAlignment;
}

void Character::setAlignment(int al)
{
	m_iAlignment = al;
}

int Character::getHitPoints()
{
	return m_iHitPoints;
}

void Character::setHitPoints(int hp)
{
	m_iHitPoints = hp;
}

int Character::getStrength()
{
	return m_iCharTraits[0];
}

void Character::setStrength(int str)
{
	m_iCharTraits[0] = str;
}

int Character::getDexterity()
{
	return m_iCharTraits[1];
}

void Character::setDexterity(int dex)
{
	m_iCharTraits[1] = dex;
}

int Character::getConstitution()
{
	return m_iCharTraits[2];
}

void Character::setConstitution(int cn)
{
	m_iCharTraits[2] = cn;
}

int Character::getIntelligence()
{
	return m_iCharTraits[3];
}

void Character::setIntelligence(int itl)
{
	m_iCharTraits[3] = itl;
}

int Character::getWisdom()
{
	return m_iCharTraits[4];
}

void Character::setWisdom(int wis)
{
	m_iCharTraits[4] = wis;
}

int Character::getCharisma()
{
	return m_iCharTraits[5];
}

void Character::setCharisma(int chr)
{
	m_iCharTraits[5] = chr;
}

bool Character::addItem(Item* item)
{
	if(item == NULL) return false;
	if(item->m_iType == BATTLE_ITEM)
	{
		return BattleItems->addItem(item);
	}
	else
	{
		return TreasureItems->addItem(item);
	}

}

Item* Character::getItem(char* itemName)
{
	
	Item* item = BattleItems->getItem(itemName);
	if(item == NULL)
	{
		item = TreasureItems->getItem(itemName);
	}
	return item;
}

Item* Character::dropItem(char* itemName)
{
	Item* item = BattleItems->dropItem(itemName);
	if(item == NULL)
	{
		item = TreasureItems->dropItem(itemName);
	}
	return item;
}

void Character::printAll()
{
	cout << "Name: " << m_sName << "\n";
	cout << "Class: " << m_iClass << "\n";
	cout << "Alignment: " << m_iAlignment << "\n";
	cout << "Hit Points: " << m_iHitPoints << "\n";

	cout << "Strength: " << m_iCharTraits[0] << "\n";
	cout << "Dexterity: " << m_iCharTraits[1] << "\n";
	cout << "Constitution: " << m_iCharTraits[2] << "\n";
	cout << "Intelligence: " << m_iCharTraits[3] << "\n";
	cout << "Wisdom: " << m_iCharTraits[4] << "\n";
	cout << "Charisma: " << m_iCharTraits[5] << "\n";

	cout << "Battle Items: \n";
	BattleItems->printTree();
	cout << "Treasure Items: \n";
	TreasureItems->printTree();
}