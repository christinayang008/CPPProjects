#include "Possessions.h"
#include <iostream>
#include <cstring>

void add(Item *newItem, Item *&tree);
Item *find(char *itemName, Item *&tree);
void Delete(Item*& tree, char *itemName, Item*& returnItem);
void DeleteNode(Item*& tree, Item*& returnItem);
void getPred(Item* tree, Item*& pred);

Possessions::Possessions()
{
    m_pRoot = NULL;
}
Possessions::~Possessions()
{
    destroyTree(m_pRoot);
}

void Possessions::destroyTree(Item* rt)
{
    if(rt != NULL)
    {
        destroyTree(rt->m_pLeft);
        destroyTree(rt->m_pRight);   
        delete rt;
    }
}

bool Possessions::addItem(Item *newItem)
{
    if(newItem == NULL) return false;
    add(newItem, m_pRoot);
    return true;
}

void add(Item* newItem, Item* &tree)
{
    if(tree == NULL)
    {
        tree = newItem;
        newItem->m_pLeft = NULL;
        newItem->m_pRight = NULL;
    }
    else if(strcmp(newItem->m_sItemName, tree->m_sItemName)<0)
    {
        add(newItem, tree->m_pLeft);
    }
    else 
    {
        add(newItem, tree->m_pRight);
    }
}

Item *Possessions:: dropItem(char *itemName)
{
    Item *returnItem = NULL;
    Delete(m_pRoot, itemName, returnItem);
    if(returnItem != NULL)
    {
        returnItem->m_pLeft = NULL;
        returnItem->m_pRight = NULL;
    }
    return returnItem;
}

void Delete(Item*& tree, char *itemName, Item*& returnItem)
{
    if(tree == NULL)
    {
        returnItem = NULL;
        return;
    }
    if(strcmp(itemName, tree->m_sItemName)<0)
        Delete(tree->m_pLeft, itemName, returnItem);
    else if(strcmp(itemName, tree->m_sItemName)>0)
        Delete(tree->m_pRight, itemName, returnItem);
    else
        DeleteNode(tree, returnItem);
}
void DeleteNode(Item*& tree, Item*& returnItem)
{
    Item* temp = tree;
    if(tree->m_pLeft == NULL)
    {
        returnItem = tree;
        tree = tree->m_pRight;
    }
    else if(tree->m_pRight == NULL)
    {
        returnItem = tree;
        tree = tree->m_pLeft;
    }
    else
    {
        returnItem = new Item();
        strcpy(returnItem->m_sItemName, tree->m_sItemName);
        strcpy(returnItem->m_sDesc, tree->m_sDesc);
        returnItem->m_iType = tree->m_iType;
        returnItem->m_dValue = tree->m_dValue;
        returnItem->m_dWeight = tree->m_dWeight;

        Item* pred;
        getPred(tree->m_pLeft, pred);
        strcpy(tree->m_sItemName, pred->m_sItemName);
        strcpy(tree->m_sDesc, pred->m_sDesc);
        tree->m_iType = pred->m_iType;
        tree->m_dValue = pred->m_dValue;
        tree->m_dWeight = pred->m_dWeight;

        Item *trash;
        Delete(tree->m_pLeft, pred->m_sItemName, trash);
        if(trash != NULL)
        {
            delete trash;
        }
    }
}
void getPred(Item* tree, Item*& pred)
{
    while(tree->m_pRight != NULL)
    {
        tree = tree->m_pRight;
    }
    pred = tree;
}

Item *Possessions::getItem(char *itemName)
{
    return find(itemName, m_pRoot);
}

Item *find(char *itemName, Item *&tree)
{
    if(tree == NULL)
    {
        return NULL;
    }
    else if(strcmp(itemName, tree->m_sItemName)<0)
        return find(itemName, tree->m_pLeft);
    else if(strcmp(itemName, tree->m_sItemName)>0)
        return find(itemName, tree->m_pRight);
    else
        return tree;
}

void Possessions::printAll(Item *rt)
{
    if(rt != NULL)
    {
        printAll(rt->m_pLeft);
        printOne(rt);
        printAll(rt->m_pRight);
    }
}

void Possessions::printOne(Item *item)
{
    cout << "\nItem Name: " << item->m_sItemName << endl;
    cout << "Description: " << item->m_sDesc << endl;
    cout << "Type: " << item->m_iType << endl;
    cout << "Value: " << item->m_dValue << endl;
    cout << "Weight: " << item->m_dWeight << endl;
}
void Possessions::printTree()
{
    printAll(m_pRoot);
}