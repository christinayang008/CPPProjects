#include "CharacterList.h"
#include <cstring>

CharacterList::CharacterList()
{
	m_pHead = NULL;
}

CharacterList::~CharacterList()
{
	Character* current = m_pHead;
	while (current != NULL)
	{
		Character* next = current->m_pNext;
		delete current;
		current = next;
	}
	m_pHead = NULL;
}

bool CharacterList::addCharacter(Character* newCharacter)
{
	if (m_pHead == NULL || strcmp(newCharacter->getName(), m_pHead->getName()) < 0)
	{
		newCharacter->m_pNext = m_pHead;
		m_pHead = newCharacter;
		return true;
	}

	Character* current = m_pHead;

	while (current->m_pNext != NULL && strcmp(current->m_pNext->getName(), newCharacter->getName()) < 0)
	{
		current = current->m_pNext;
	}

	newCharacter->m_pNext = current->m_pNext;
	current->m_pNext = newCharacter;
	return true;
}

Character* CharacterList::deleteCharacter(char* characterName)
{
	Character* temp = NULL;

	if (m_pHead == NULL || characterName == NULL) return NULL;

	if (strcmp(m_pHead->getName(), characterName) == 0)
	{
		temp = m_pHead;
		m_pHead = m_pHead->m_pNext;
		temp->m_pNext = NULL;
		return temp;
	}

	Character* current = m_pHead;
	while (current->m_pNext != NULL)
	{
		if (strcmp(characterName, current->m_pNext->getName()) == 0)
		{
			temp = current->m_pNext;
			current->m_pNext = temp->m_pNext;
			temp->m_pNext = NULL;
			return temp;
		}
		current = current->m_pNext;
	}
	return NULL;
}

bool CharacterList::addItem(char* characterName, Item* newItem)
{
	Character* current = m_pHead;

	while (current != NULL)
	{
		if (strcmp(current->getName(), characterName) == 0)
		{
			return current->addItem(newItem);
		}
		current = current->m_pNext;
	}
	return false;
}

Item* CharacterList::getItem(char* characterName, char* itemName)
{
	Character* current = m_pHead;

	while (current != NULL)
	{
		if (strcmp(current->getName(), characterName) == 0)
		{
			return current->getItem(itemName);
		}
		current = current->m_pNext;
	}
	return NULL;
}

Item* CharacterList::dropItem(char* characterName, char* itemName)
{
	Character* current = m_pHead;

	while (current != NULL)
	{
		if (strcmp(current->getName(), characterName) == 0)
		{
			return current->dropItem(itemName);
		}
		current = current->m_pNext;
	}
	return NULL;
}

void CharacterList::printCharacters()
{
	Character* current = m_pHead;

	if (current == NULL)
	{
		cout << "Empty List.\n";
		return;
	}

	while (current != NULL)
	{
		current->printAll();
		cout << "\n";
		current = current->m_pNext;
	}
}