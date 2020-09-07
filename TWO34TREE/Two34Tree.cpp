// Specification of ADT 2-3-4 Tree
//     data object: a 2-3-4 tree (a tree containing 2-nodes,
//                  3-nodes, and 4-nodes) where a k-node has
//                  k children
// note: this is not the formal definition that takes 2 pages in textbook
//     operations: create, destroy, insert, display
// Programmer: dr y and Mason Dellutri and Kevin Shaw    Date: May 2nd, 2018
// Filename: Two34Tree.cpp
//
// class Two34TreeNode specifies and implements a node for a
//    2-3-4 tree with room for 1-3 data items from class citem and
//    0-4 children

#include "Two34Tree.h"
#include "Two34TreeNode.h"
#include <iostream>
using namespace std;

	
   // frees the heap memory of a tree
   // pre: treep is assigned but may be empty
   // post: all nodes in the tree with root treep
   //       have been released back to the heap and
   //       treep is empty
   // usage: destroyTree (mroot);
   void destroyTree(Two34TreeNode*& treep)
   {
	    if (not(treep == nullptr))
		{
			for (int k = 0; k < 4; k++)
			{
				destroyTree(treep -> kids[k]);
			}
			delete treep;
			treep = nullptr;
		}
   }
	
	bool isTwoNode(Two34TreeNode *treep)
    {

	    if((not(treep -> keys[0].isEmpty())) and treep -> keys[1].isEmpty() and treep -> keys[2].isEmpty())
			return true;
		else
			return false;
    }
   
    bool isThreeNode(Two34TreeNode *treep)
    {
	    if((not(treep -> keys[0].isEmpty())) and (not(treep -> keys[1].isEmpty())) and treep -> keys[2].isEmpty())
			return true;
		else
			return false;
    }
	
    bool isFourNode(Two34TreeNode *treep)
	{
    
	    if((not(treep -> keys[0].isEmpty())) and (not(treep -> keys[1].isEmpty())) and (not(treep -> keys[2].isEmpty())))
			return true;
		else
			return false;
    }
	
   // shows the data in the tree in inorder
   // pre: treep is assigned but may be empty
   //      output is open
   // post: the data items in the nodes of treep's tree
   //       are printed to output in inorder
   void inorder(ostream& output, Two34TreeNode* treep)
   {
	    if (not(treep == nullptr))
		{
			inorder(output, treep -> kids[0]);
			inorder(output, treep -> kids[1]);
			for (int k = 0; k < 3; k++)
			{
				output << treep -> kids[k] << " ";
			}
			inorder(output, treep -> kids[2]);
			inorder(output, treep -> kids[3]);
		}
   }
	
	   // shows the data in the tree in its tree structure
   // pre: output is open. treep is assigned a tree.
   //      level is assigned
   // post: the data items of the nodes of treep at level
   //       in the tree are printed to output with spacing
   //       to denote the level.
   // usage: pretty (output, mroot, 1);
   void pretty(ostream& output, Two34TreeNode* treep, int level)
   {
	    if (not(treep == nullptr))
		{
			if(isTwoNode(treep))
			{
				pretty(output, treep->kids[1], level + 1);
				for (int k = 0; k < level; k++)
				{
					output << "         ";
				}
				for (int k = 0; k < 3; k++)
				{
					if (not(treep->keys[k].isEmpty()))
					{
						output << treep->keys[k] << " ";
					}
				}
				output << endl;
				pretty(output, treep->kids[0], level + 1);
				if (not(treep->kids[0] == nullptr))
				{
					output << endl;
				}
			}
			else
			{
				pretty(output, treep -> kids[3], level + 1);
				pretty(output, treep -> kids[2], level + 1);
				for (int k = 0; k < level; k++)
				{
					output << "         ";
				}
				for (int k = 0; k < 3; k++)
				{
					if (not(treep->keys[k].isEmpty()))
					{
						output << treep->keys[k] << " ";
					}
				}
				output << endl;
				pretty(output, treep->kids[1], level + 1);
				pretty(output, treep->kids[0], level + 1);
				if (not(treep->kids[0] == nullptr))
				{
					output << endl;
				}
			}
		}
   }

	
	void noPointerInsert(Two34TreeNode *treep, const Key& newKey)
	{
		cout << "no pointer insert" << endl;
		if(isTwoNode(treep))//if there is one key in the node
		{
			cout << "one key" << endl;
			if(newKey < treep -> keys[0])
			{
				treep -> keys[1] = treep -> keys[0];	
				treep -> keys[0] = newKey;			
			}
			else
			{
				treep -> keys[1] = newKey;		
			}
		}
		else if(isThreeNode(treep))//if there are two keys in the node
		{
			cout << "two keys" << endl;
			if((newKey < treep -> keys[0]) and (newKey < treep -> keys[1]))//less than all
			{
				treep -> keys[2] = treep -> keys[1];
				treep -> keys[1] = treep -> keys[0];				
				treep -> keys[0] = newKey;			
			}
			else if((not(newKey < treep -> keys[0])) and (newKey < treep -> keys[1]))//goes in middle
			{
				treep -> keys[2] = treep -> keys[1];				
				treep -> keys[1] = newKey;			
			}
			else//goes at end
			{
				treep -> keys[2] = newKey;		
			}
		}
		else if(isFourNode(treep))//there are three keys in the node
		{
			
			cout << "three keys, splitting" << endl;
			Two34TreeNode* leftNode; leftNode = new Two34TreeNode;
			Two34TreeNode* rightNode; rightNode = new Two34TreeNode;
			//make the two new nodes and drop down the lower and upper keys
			leftNode -> keys[0] = treep -> keys[0];
			rightNode -> keys[0] = treep -> keys[2];
			treep -> keys[0] = treep -> keys[1];
			treep -> keys[1].emptyIt();
			treep -> keys[2].emptyIt();
			treep -> kids[0] = leftNode;//assign pointers
			treep -> kids[1] = rightNode;
			if((newKey < treep -> keys[0]))//check if it goes to left or right
			{
				if(newKey < leftNode -> keys[0])
				{
					leftNode -> keys[1] = leftNode -> keys[0];	
					leftNode -> keys[0] = newKey;
				}
				else
				{
					leftNode -> keys[1] = newKey;
				}
				
			}
			else//if went to right
			{
				if(newKey < rightNode -> keys[0])
				{
					rightNode -> keys[1] = rightNode -> keys[0];	
					rightNode -> keys[0] = newKey;
				}
				else
				{
					rightNode -> keys[1] = newKey;
				}
			}
			
		}	
		else//there are no keys in the node
		{
				treep -> keys[0] = newKey;
		}
	}
	
	void twoKidsNotFullInsert(Two34TreeNode *treep, const Key& newKey, bool isLeft)
	{
		cout << "is two kids not full insert" << endl;
		Two34TreeNode* leftNode; leftNode = new Two34TreeNode;
		Two34TreeNode* rightNode; rightNode = new Two34TreeNode;
		//make the two new nodes and drop down the lower and upper keys
		leftNode = treep -> kids[0];
		rightNode = treep -> kids[1];
		if(isLeft)//check if it goes to left or right
		{
			if(newKey < leftNode -> keys[0])//if went to left
			{
				leftNode -> keys[2] = leftNode -> keys[1];
				leftNode -> keys[1] = leftNode -> keys[0];	
				leftNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < leftNode -> keys[0])) and newKey < leftNode -> keys[1]) or leftNode -> keys[1].isEmpty())
			{
				leftNode -> keys[2] = leftNode -> keys[1];
				leftNode -> keys[1] = newKey;		
			}
			else 
			{
				leftNode -> keys[2] = newKey;
			}
			treep -> kids[0] = leftNode;
		}
		else//if went to right
		{
			if(newKey < rightNode -> keys[0])
			{
				rightNode -> keys[2] = rightNode -> keys[1];
				rightNode -> keys[1] = rightNode -> keys[0];	
				rightNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < rightNode -> keys[0])) and newKey < rightNode -> keys[1]) or rightNode -> keys[1].isEmpty())
			{
				rightNode -> keys[2] = rightNode -> keys[1];
				rightNode -> keys[1] = newKey;		
			}
			else 
			{
				rightNode -> keys[2] = newKey;
			}
			treep -> kids[1] = rightNode;
		}
	}
	
	void twoKidsFullInsert(Two34TreeNode *treep, const Key& newKey, bool isLeft)
	{
		cout << "is two kids full insert" << endl;
		Two34TreeNode* tempNode;  tempNode = new Two34TreeNode;
		Two34TreeNode* leftNode;  leftNode = new Two34TreeNode;
		Two34TreeNode* rightNode;  rightNode = new Two34TreeNode;
		//make the two new nodes and drop down the lower and upper keys
		
		if(isLeft)//check if it goes to left or right
		{
			tempNode = treep -> kids[0];
			if(newKey < tempNode -> keys[0])//if went to left
			{
				treep -> keys[1] = treep -> keys[0];//splitting and bringing it up
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[1] = tempNode -> keys[0];
				leftNode -> keys[0] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[2] = treep -> kids[1];
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and newKey < tempNode -> keys[1])
			{
				treep -> keys[1] = treep -> keys[0];
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				leftNode -> keys[1] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[2] = treep -> kids[1];	
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and (not(newKey < leftNode -> keys[1])) and newKey < tempNode -> keys[2])
			{
				treep -> keys[1] = treep -> keys[0];
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[1] = tempNode -> keys[2];
				rightNode -> keys[0] = newKey;
				treep -> kids[2] = treep -> kids[1];	
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
			else 
			{
				treep -> keys[1] = treep -> keys[0];
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[0] = tempNode -> keys[2];
				rightNode -> keys[1] = newKey;
				treep -> kids[2] = treep -> kids[1];	
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
		}
		else//if went to right
		{
			tempNode = treep -> kids[1];
			if(newKey < tempNode -> keys[0])//if went to left
			{
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[1] = tempNode -> keys[0];
				leftNode -> keys[0] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and newKey < tempNode -> keys[1])
			{
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				leftNode -> keys[1] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and (not(newKey < tempNode -> keys[1])) and newKey < tempNode -> keys[2])
			{
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[1] = tempNode -> keys[2];
				rightNode -> keys[0] = newKey;				
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
			else 
			{
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[0] = tempNode -> keys[2];
				rightNode -> keys[1] = newKey;				
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
		}
	}
	
	void threeKidsNotFullInsert(Two34TreeNode *treep, const Key& newKey)
	{
		cout << "is three kids not full insert" << endl;
		Two34TreeNode* leftNode;  leftNode = new Two34TreeNode;
		Two34TreeNode* middleNode; middleNode = new Two34TreeNode;
		Two34TreeNode* rightNode;  rightNode = new Two34TreeNode;
		//make the three new nodes and drop down the lower and upper keys
		leftNode = treep -> kids[0];
		middleNode = treep -> kids[1];
		rightNode = treep -> kids[2];
		if(newKey < treep -> keys[0])//check if it goes to left or right
		{
			if(newKey < leftNode -> keys[0])//if went to left
			{
				leftNode -> keys[2] = leftNode -> keys[1];
				leftNode -> keys[1] = leftNode -> keys[0];	
				leftNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < leftNode -> keys[0])) and newKey < leftNode -> keys[1]) or leftNode -> keys[1].isEmpty())
			{
				leftNode -> keys[2] = leftNode -> keys[1];
				leftNode -> keys[1] = newKey;		
			}
			else 
			{
				leftNode -> keys[2] = newKey;
			}
			treep -> kids[0] = leftNode;
		}
		else if ((not(newKey < treep -> keys[0])) and newKey < treep -> keys[1])//goes middle
		{
			if(newKey < middleNode -> keys[0])
			{
				middleNode -> keys[2] = middleNode -> keys[1];	
				middleNode -> keys[1] = middleNode -> keys[0];	
				middleNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < middleNode -> keys[0])) and newKey < middleNode -> keys[1]) or middleNode -> keys[1].isEmpty())
			{
				middleNode -> keys[2] = middleNode -> keys[1];
				middleNode -> keys[1] = newKey;		
			}
			else 
			{
				middleNode -> keys[2] = newKey;
			}
			treep -> kids[1] = middleNode;
		}
		else//goes right
		{
			if(newKey < rightNode -> keys[0])
			{
				rightNode -> keys[2] = rightNode -> keys[1];	
				rightNode -> keys[1] = rightNode -> keys[0];	
				rightNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < rightNode -> keys[0])) and newKey < rightNode -> keys[1]) or rightNode -> keys[1].isEmpty())
			{
				rightNode -> keys[2] = rightNode -> keys[1];
				rightNode -> keys[1] = newKey;		
			}
			else 
			{
				rightNode -> keys[2] = newKey;
			}
			treep -> kids[2] = rightNode;
		}
	}
	
	void threeKidsFullInsert(Two34TreeNode *treep, const Key& newKey)
	{
		cout << "is three kids full insert" << endl;
		Two34TreeNode* tempNode;  tempNode = new Two34TreeNode;
		Two34TreeNode* leftNode;  leftNode = new Two34TreeNode;
		Two34TreeNode* rightNode;  rightNode = new Two34TreeNode;
		//make the two new nodes and drop down the lower and upper keys
		
		if(newKey < treep -> keys[0])//check if it goes to left or middle or right
		{
			tempNode = treep -> kids[0];//if went to left
			if(newKey < tempNode -> keys[0])
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = treep -> keys[0];
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[1] = tempNode -> keys[0];
				leftNode -> keys[0] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = treep -> kids[1];
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and newKey < tempNode -> keys[1])
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = treep -> keys[0];
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				leftNode -> keys[1] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = treep -> kids[1];
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and (not(newKey < tempNode -> keys[1])) and newKey < tempNode -> keys[2])
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = treep -> keys[0];
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[1] = tempNode -> keys[2];
				rightNode -> keys[0] = newKey;
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = treep -> kids[1];
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
			else 
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = treep -> keys[0];
				treep -> keys[0] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[0] = tempNode -> keys[2];
				rightNode -> keys[1] = newKey;
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = treep -> kids[1];
				treep -> kids[1] = rightNode;
				treep -> kids[0] = leftNode;
			}
		}
		else if ((not(newKey < treep -> keys[0])) and (newKey < treep -> keys[1]))//if went to middle
		{
			tempNode = treep -> kids[1];
			if(newKey < tempNode -> keys[0])
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[1] = tempNode -> keys[0];
				leftNode -> keys[0] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and newKey < tempNode -> keys[1])
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				leftNode -> keys[1] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and (not(newKey < tempNode -> keys[1])) and newKey < tempNode -> keys[2])
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[1] = tempNode -> keys[2];
				rightNode -> keys[0] = newKey;
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
			else if((not(newKey < tempNode -> keys[0])) and (not(newKey < tempNode -> keys[1])) and newKey < tempNode -> keys[2])
			{
				treep -> keys[2] = treep -> keys[1];//splitting and bringing it up
				treep -> keys[1] = tempNode -> keys[1];	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[0] = tempNode -> keys[2];
				rightNode -> keys[1] = newKey;
				treep -> kids[3] = treep -> kids[2];
				treep -> kids[2] = rightNode;
				treep -> kids[1] = leftNode;
			}
		}
		else//if went to right
		{
			tempNode = treep -> kids[2];
			if(newKey < tempNode -> keys[0])
			{
				treep -> keys[2] = tempNode -> keys[1];//splitting and bringing it up	
				leftNode -> keys[1] = tempNode -> keys[0];
				leftNode -> keys[0] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[3] = rightNode;
				treep -> kids[2] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and newKey < tempNode -> keys[1])
			{
				treep -> keys[2] = tempNode -> keys[1];//splitting and bringing it up	
				leftNode -> keys[0] = tempNode -> keys[0];
				leftNode -> keys[1] = newKey;
				rightNode -> keys[0] = tempNode -> keys[2];
				treep -> kids[3] = rightNode;
				treep -> kids[2] = leftNode;
			}
			else if ((not(newKey < tempNode -> keys[0])) and (not(newKey < tempNode -> keys[1])) and newKey < tempNode -> keys[2])
			{
				treep -> keys[2] = tempNode -> keys[1];//splitting and bringing it up	
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[1] = tempNode -> keys[2];
				rightNode -> keys[0] = newKey;
				treep -> kids[3] = rightNode;
				treep -> kids[2] = leftNode;
			}
			else 
			{
				treep -> keys[2] = tempNode -> keys[1];//splitting and bringing it up
				leftNode -> keys[0] = tempNode -> keys[0];
				rightNode -> keys[0] = tempNode -> keys[2];
				rightNode -> keys[1] = newKey;
				treep -> kids[3] = rightNode;
				treep -> kids[2] = leftNode;
			}
		}
	}
	
	void fourKidsNotFullInsert(Two34TreeNode *treep, const Key& newKey)
	{
		cout << "is four kids not full insert" << endl;
		Two34TreeNode* leftNode;  leftNode = new Two34TreeNode;
		Two34TreeNode* middleNode;  middleNode = new Two34TreeNode;
		Two34TreeNode* rightNode;  rightNode = new Two34TreeNode;
		Two34TreeNode* lastNode;  lastNode = new Two34TreeNode;
		//make the two new nodes and drop down the lower and upper keys
		leftNode = treep -> kids[0];
		middleNode = treep -> kids[1];
		rightNode = treep -> kids[2];
		lastNode = treep -> kids[3];
		if((newKey < treep -> keys[0]))//check if it goes to left or right
		{
			if(newKey < leftNode -> keys[0])//if went to left
			{
				leftNode -> keys[2] = leftNode -> keys[1];	
				leftNode -> keys[1] = leftNode -> keys[0];	
				leftNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < leftNode -> keys[0])) and newKey < leftNode -> keys[1]) or leftNode -> keys[1].isEmpty())
			{
				leftNode -> keys[2] = leftNode -> keys[1];
				leftNode -> keys[1] = newKey;		
			}
			else 
			{
				leftNode -> keys[2] = newKey;
			}
			treep -> kids[0] = leftNode;
		}
		else if ((not(newKey < treep -> keys[0])) and newKey < treep -> keys[1])//goes middle
		{
			if(newKey < middleNode -> keys[0])
			{
				middleNode -> keys[2] = middleNode -> keys[1];	
				middleNode -> keys[1] = middleNode -> keys[0];	
				middleNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < middleNode -> keys[0])) and newKey < middleNode -> keys[1]) or middleNode -> keys[1].isEmpty())
			{
				middleNode -> keys[2] = middleNode -> keys[1];
				middleNode -> keys[1] = newKey;		
			}
			else 
			{
				middleNode -> keys[2] = newKey;
			}
			treep -> kids[1] = middleNode;
		}
		else if ((not(newKey < treep -> keys[0])) and (not(newKey < treep -> keys[1])) and newKey < treep -> keys[2])
		{
			if(newKey < rightNode -> keys[0])
			{
				rightNode -> keys[2] = rightNode -> keys[0];	
				rightNode -> keys[1] = rightNode -> keys[0];	
				rightNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < rightNode -> keys[0])) and newKey < rightNode -> keys[1]) or rightNode -> keys[1].isEmpty())
			{
				rightNode -> keys[2] = rightNode -> keys[1];
				rightNode -> keys[1] = newKey;		
			}
			else 
			{
				rightNode -> keys[2] = newKey;
			}
			treep -> kids[2] = rightNode;
		}
		else
		{
			if(newKey < lastNode -> keys[0])
			{
				lastNode -> keys[2] = lastNode -> keys[1];	
				lastNode -> keys[1] = lastNode -> keys[0];	
				lastNode -> keys[0] = newKey;			
			}
			else if (((not(newKey < lastNode -> keys[0])) and newKey < lastNode -> keys[1]) or lastNode -> keys[1].isEmpty())
			{
				lastNode -> keys[2] = lastNode -> keys[1];
				lastNode -> keys[1] = newKey;		
			}
			else 
			{
				lastNode -> keys[2] = newKey;
			}
			treep -> kids[3] = lastNode;
		}
	}
	
	void fourKidsFullInsert(Two34TreeNode *treep, const Key& newKey)
	{
		cout << "is four kids full insert" << endl;
		Two34TreeNode* tempNode;  tempNode = new Two34TreeNode;
		if((newKey < treep -> keys[0]))//check if it goes to left or right
		{
			tempNode = treep -> kids[0];
			treep -> kids[0] = tempNode;
		}
		else if ((not(newKey < treep -> keys[0])) and (newKey < treep -> keys[1]))
		{
			tempNode = treep -> kids[1];
			treep -> kids[1] = tempNode;
		}
		else if ((not(newKey < treep -> keys[0])) and (not(newKey < treep -> keys[1])) and newKey < treep -> keys[2])
		{
			tempNode = treep -> kids[2];
			treep -> kids[2] = tempNode;
		}
		else 
		{
			tempNode = treep -> kids[3];
			treep -> kids[3] = tempNode;
		}
		Two34TreeNode* leftNode;  leftNode = new Two34TreeNode;
		Two34TreeNode* rightNode;  rightNode = new Two34TreeNode;
		//make the two new nodes and drop down the lower and upper keys
		leftNode -> keys[0] = tempNode -> keys[0];
		tempNode -> keys[0] = tempNode -> keys[1];
		tempNode -> keys[1].emptyIt();
		rightNode -> keys[0] = tempNode -> keys[2];
		tempNode -> keys[2].emptyIt();
		tempNode -> kids[0] = leftNode;//assign pointers
		tempNode -> kids[1] = rightNode;
		if((newKey < tempNode -> keys[0]))//check if it goes to left or right
		{
			if(newKey < leftNode -> keys[0])//if went to left
			{
				leftNode -> keys[1] = leftNode -> keys[0];	
				leftNode -> keys[0] = newKey;			
			}
			else 
			{
				leftNode -> keys[1] = newKey;
			}
		}
		else//if went to right
		{
			if(newKey < rightNode -> keys[0])
			{
				rightNode -> keys[1] = rightNode -> keys[0];	
				rightNode -> keys[0] = newKey;			
			}
			else 
			{
				rightNode -> keys[1] = newKey;
			}
		}
	}
	
   // creates an empty 2-3-4 Tree
   // post: object is empty
   Two34Tree::Two34Tree()
   {
	   root = nullptr;
   }

   // destroys a 2-3-4 Tree
   // pre: object exists
   // post: object does not exist, all pre-memory released
   Two34Tree::~Two34Tree()
   {
	   delete root;
	   root = nullptr;
   }

   // inserts a new key into the tree
   // pre: tree object exists. newKey is assigned.
   // post: newKey is placed in the appropriately sorted
   //       position in the 2-3-4 tree object
   // usage: tree.insert(mykey);
   void Two34Tree::insert(const Key& newKey)
   {
	   if(root == nullptr)
	   {
		   root = new Two34TreeNode(newKey);
	   }
	   else if(root -> kids[0] == nullptr)
	   {
		   noPointerInsert(root, newKey);
	   }
	   else
	   {
		    Two34TreeNode* treep; 
			Two34TreeNode* parent;
			Two34TreeNode* tempNode;  tempNode = new Two34TreeNode;
			treep = root;
		    while( not(treep == nullptr)) //finds the parent node
		    {
				parent = treep;
			    if(newKey < treep -> keys[0])
				{
					cout << "first if" << endl;
					treep = treep -> kids[0];
					if (not(treep == nullptr))
					{
						if( treep -> kids[0] == nullptr)
						{
							treep = nullptr;
						}
					}
				}
				else if (((not(newKey < treep -> keys[0])) and (newKey < treep -> keys[1])) or treep -> keys[1].isEmpty())
				{
					cout << "second if" << endl;
					treep = treep -> kids[1];
					if (not(treep == nullptr))
					{
						if( treep -> kids[0] == nullptr)
						{
						treep = nullptr;
						}
					}
					
				}
				else if (((not(newKey < treep -> keys[0])) and (not(newKey < treep -> keys[1])) and newKey < treep -> keys[2]) or treep -> keys[2].isEmpty())
				{
					cout << "third if" << endl;
					treep = treep -> kids[2];
					if (not(treep == nullptr))
					{
						if( treep -> kids[0] == nullptr)
						{
							treep = nullptr;
						}
					}
				}
				else 
				{
					cout << "last else" << endl;
					treep = treep -> kids[3];
					if (not(treep == nullptr))
					{
						if( treep -> kids[0] == nullptr)
						{
							treep = nullptr;
						}
					}
				}
				
		    }
			if (isTwoNode(parent))
			{
				cout << "is in twoNode if "<< endl;
				bool isLeft;
				if((newKey < parent -> keys[0]))//check if it goes to left or right
				{
					tempNode = parent -> kids[0];
					isLeft = true;
				}
				else 
				{
					tempNode = parent -> kids[1];
					isLeft = false;
				}
				
				if (tempNode -> keys[2].isEmpty())
				{
					twoKidsNotFullInsert(parent, newKey, isLeft);
				}
				else
				{
					twoKidsFullInsert(parent, newKey, isLeft);
				}
			}
			else if (isThreeNode(parent))
			{
				if((newKey < parent -> keys[0]))//check if it goes to left or right
				{
					tempNode = parent -> kids[0];
				}
				else if ((not(newKey < parent -> keys[0])) and (newKey < parent -> keys[1]))
				{
					tempNode = parent -> kids[1];
				}
				else 
				{
					tempNode = parent -> kids[2];
				}
				
				cout << "tempNode -> keys[2] " << tempNode -> keys[2] << endl;
				if (tempNode -> keys[2].isEmpty())
				{
					threeKidsNotFullInsert(parent, newKey);
				}
				else
				{
					threeKidsFullInsert(parent, newKey);
				}
			}
			else if (isFourNode(parent))
			{
				if((newKey < parent -> keys[0]))//check if it goes to left or right
				{
					tempNode = parent -> kids[0];
				}
				else if ((not(newKey < parent -> keys[0])) and (newKey < parent -> keys[1]))
				{
					tempNode = parent -> kids[1];
				}
				else if ((not(newKey < parent -> keys[0])) and (not(newKey < parent -> keys[1])) and newKey < parent -> keys[2])
				{
					tempNode = parent -> kids[2];
				}
				else 
				{
					tempNode = parent -> kids[3];
				}
				
				if (tempNode -> keys[2].isEmpty())
				{
					fourKidsNotFullInsert(parent, newKey);
				}
				else
				{
					fourKidsFullInsert(parent, newKey);
				}
			}		
			else
			{
				cout << "You messed up" << endl;
			}
	   }
	   cout << "gets to end of insert" << endl;
   }

   // displays a tree in one of two formats
   // pre: which is either 'i' or 'p'
   //      output is open
   // post: if which is 'i' the tree is displayed inorder
   //       else the tree is displayed showing its tree
   //       structure
   // usage: tree.display (cout, 'p');
   void Two34Tree::display(ostream& output, char which)
   {
	    if (which == 'i')
		{
			inorder(output, root);
		}
		else
		{
			pretty(output, root, 0);
		}
		 cout << "gets to end of display" << endl;
   }
