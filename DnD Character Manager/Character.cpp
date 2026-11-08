#include "Character.h"

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

	for (int i = 0; i < 10; i++)
	{
		m_Items[i].m_sItemName[0] = '\0';
		m_Items[i].m_iType = -1;
		m_Items[i].m_dValue = 0.0;
		m_Items[i].m_dWeight = 0.0;
	}
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

	for (int i = 0; i < 10; i++)
	{
		m_Items[i].m_sItemName[0] = '\0';
		m_Items[i].m_dValue = 0.0;
		m_Items[i].m_dWeight = 0.0;
		m_Items[i].m_iType = -1;
	}
}

Character::~Character()
{

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
	for (int i = 0; i < 10; i++)
	{
		if (m_Items[i].m_sItemName[0] == '\0')
		{
			strcpy(m_Items[i].m_sItemName, item->m_sItemName);
			m_Items[i].m_iType = item->m_iType;
			m_Items[i].m_dValue = item->m_dValue;
			m_Items[i].m_dWeight = item->m_dWeight;
			return true;
		}
	}
	return false;
}

Item* Character::getItem(char* itemName)
{
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(m_Items[i].m_sItemName, itemName) == 0)
		{
			return &m_Items[i];
		}
	}
	return NULL;
}

Item* Character::dropItem(char* itemName)
{
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(m_Items[i].m_sItemName, itemName) == 0)
		{
			Item* temp = new Item();
			strcpy(temp->m_sItemName, m_Items[i].m_sItemName);
			temp->m_iType = m_Items[i].m_iType;
			temp->m_dValue = m_Items[i].m_dValue;
			temp->m_dWeight = m_Items[i].m_dWeight;

			m_Items[i].m_sItemName[0] = '\0';
			m_Items[i].m_iType = -1;
			m_Items[i].m_dValue = 0.0;
			m_Items[i].m_dWeight = 0.0;

			return temp;
		}
	}
	return NULL;
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
}