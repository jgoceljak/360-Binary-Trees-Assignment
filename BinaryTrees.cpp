#include<iostream> 
using namespace std; 

class TreeChunk { 
public: 
  int value; 
  TreeChunk *left; 
  TreeChunk *right; 
  
  TreeChunk(){ 
    value = 0;
    left = right = NULL;
  }
};

class BST{
  public:
  TreeChunk *root;

  BST(){
    root = NULL;
  }

  void addValue(int value){
    //check if empty
    if(root == NULL) { 
      root = new TreeChunk; 
      root->value = value; 
      return; 
    }
    TreeChunk *fast, *slow;
    fast = root;
    slow = root;

    while(fast != NULL){
      slow = fast;

      if (fast->value == value){
        cout << "This is a duplicate value" << endl;
        return;
      }
      else if(value < fast->value){
        fast = fast->left;
      }
      else if(value > fast->value){
        fast = fast->right;
      }
    }
     if(fast == NULL) {
    	TreeChunk *temp = new TreeChunk; 
	    temp->value = value; 

	  if(value < slow->value) {
		  slow->left = temp;
     } else {
	  	slow->right = temp; 
     }	
    }
  }
    
  void searchBST(int key, TreeChunk *start) { 
      if(start == NULL) {
	    cout << "Value not found" << endl; 
	} else {
    	if(key == start->value) { 
	   		cout << "Value found" << endl; 
		}
		else if(key > start->value) {
	   		 searchBST(key, start->right); 
		}
		else { 
	   		searchBST(key, start->left);
		}
  }
  }
  int minValTree(TreeChunk *start){
      if(start == NULL){
        return -1;
      }
      while (start->left != NULL){
        start = start->left;
      }
      return start->value;
    }
 void deleteNode(int key, TreeChunk *start){
  if(start == NULL){
      cout << "Can't find this value, will not delete" << endl;
    }
   TreeChunk *slow, *fast;
   slow = fast = start;
  while(fast != NULL && key != fast->value){
    slow = fast;
    if (key > fast->value){
      fast = fast->right;
     } else {
       fast = fast->left;
     }      
   }
   if(fast == NULL){
      cout << "Value not found.\n";
      return;
    }

   if(key == fast->value){
     if(fast->left == NULL && fast->right == NULL){
        cout << "===============\n";
        cout << "Case I delete\n";
        if (slow->left == fast){
          slow->left = NULL;
          cout << "About to delete: " << fast->value << "\n";
          delete fast;
        }else{
          slow->right = NULL;
          cout << "About to delete: " << fast->value << "\n";
          delete fast;
        }
     } else if(fast->left == NULL && fast->right != NULL){
        cout << "===============\n";
        cout << "Case II delete\n";
        if(slow->left == fast){
          slow->left = fast->right;
        }else{
          slow->right = fast->right;
        }
        cout << "About to delete: " << fast->value << "\n";
        delete fast;
      } else if(fast->left != NULL && fast->right == NULL){
        cout << "===============\n";
        cout << "Case II delete\n";
        if (slow->left == fast) {
          slow->left = fast->left;
        } else {
          slow->right = fast->left;
        }
        cout << "About to delete: " << fast->value << "\n";
        delete fast;
      } else{

        cout << "===============\n";
        cout << "Case III delete\n";
        int swap = minValTree(fast->right);
        fast->value = swap;
        deleteNode(swap, fast->right);
      }
      
   }
 }
  void inorder(TreeChunk *start) {
  	if(start == NULL) {
		return; 
	}
	else { 
		//left, root, right 
		inorder(start->left);
	        cout << start->value << "  " << endl; 
		inorder(start->right); 	
	}
  }

  void preorder(TreeChunk *start) { 
  	if(start == NULL) 
		return; 
	else { 
		cout << start->value << " " << endl; 
		preorder(start->left); 
		preorder(start->right); 
	}
  }

  void postorder(TreeChunk *start) { 
  	if(start == NULL) 
		return; 
	else {
		postorder(start->left); 
		postorder(start->right); 
		cout << start->value << "  " << endl; 
	}
  }


  void deleteTree(TreeChunk *start){
    if (start == NULL) {
      return;
    }

    deleteTree(start->left);
    deleteTree(start->right);
     
    cout << "\n Deleting node: " << start->value;
    delete start;
    root = NULL;

}
bool checkBalance(TreeChunk *start){
    int leftLength; 
    int rightLength;

    if (start == NULL) {
        return 1;
    }
 
    leftLength = length(start->left);
    rightLength = length(start->right);
 
    if (abs(leftLength - rightLength) <= 1 && checkBalance(start->left) && checkBalance(start->right)){
        return 1;
    }
    return 0;
}
int max(int a, int b){
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

int length(TreeChunk* start)
{

    if (start == NULL){
        return 0;
    } else {
      return 1 + max(length(start->left), length(start->right));
    }
}

int firstCommonParent(int value1, int value2){
      TreeChunk *fast, *slow;
      fast = slow = root;

      while (fast != NULL && value1 != fast->value) {
        slow = fast;
        if (value1 < fast->value) {
          fast = fast->left;
        } else {
          fast = fast->right;
        }
      }

      if(fast == NULL){
        cout << "Value 1 not in tree\n";
        return -1;
      }

      fast = slow = root;

      while (fast != NULL && value2 != fast->value) {
        slow = fast;
        if (value2 < fast->value) {
          fast = fast->left;
        } else {
          fast = fast->right;
        }
      }

      if (fast == NULL) {
        cout << "Value 2 not in tree\n";
        return -1;
      }

      TreeChunk *temp = _firstCommonParent(root, value1, value2);
      return temp->value;
    }

    TreeChunk *_firstCommonParent(TreeChunk *start, int value1, int value2){
      if (start == NULL) return NULL;
      if (start->value == value1 || start->value == value2) {
        return start;
      }

      TreeChunk *leftCP = _firstCommonParent(start->left, value1, value2);
      TreeChunk *rightCP = _firstCommonParent(start->right, value1, value2);

      if (leftCP && rightCP) return start;

      if(leftCP != NULL){
        return leftCP;
      }else{
        return rightCP;
      }
    }
 
  
};

int main() 
{
  BST tree; 
  int choice, value, key, key2; 
  tree.addValue(30);
  tree.addValue(15); 
  tree.addValue(60);
  tree.addValue(7); 
  tree.addValue(22); 
  tree.addValue(45); 
  tree.addValue(17); 
  tree.addValue(27); 
  tree.addValue(75); 
 
  while(1) { 
  cout << '\n' << endl;
  cout << "Press 1 to add a new value" << endl; 
	cout << "Press 2 to search" << endl; 
	cout << "Press 3 for in-order" << endl; 
	cout << "Press 4 for pre-order" << endl; 
	cout << "Press 5 for post-order" << endl; 
	cout << "Press 6 for deleteing node" << endl; 
  cout << "Press 7 to delete entire tree" << endl; 
  cout << "Press 8 to check balance" << endl; 
  cout << "Press 9 to find nearest common parent of two values" << endl;
  cout << "Press anything else to exit" << endl;
	cin >> choice; 

	switch(choice) { 
	  case 1: cout << "What value did you want to add?" << endl; 
		  cin >> value;
		  tree.addValue(value); 
		  break; 

	  case 2: cout << "Search for what?" << endl; 
		  cin >> value;
		  tree.searchBST(value, tree.root);
		  break; 

	  case 3: tree.inorder(tree.root); 
		  break; 

	  case 4: tree.preorder(tree.root); 
		  break; 

	  case 5: tree.postorder(tree.root); 
		  break; 

    case 6 : cout << "Enter value to delete: \n";
      cin >> value;
      tree.deleteNode(value, tree.root);
      break;

    case 7 : 
      cout << "Deleting Entire Tree" << endl;
      tree.deleteTree(tree.root);
      cout << "\n Tree Deleted" << endl;
      break;

    case 8 : 
    if (tree.checkBalance(tree.root)) {
      cout << "Balanced" << endl;
    } else {
      cout << "Not Balanced" << endl;
    }
    break;

    case 9:
        cout << "Enter first value:";
        cin >> key;
        cout << "Enter second value:";
        cin >> key2;
        cout << "Nearest common parent is: " << tree.firstCommonParent(key, key2) << "\n";
        break;

	  default: cout << "Goodbye!" << endl; 
		  exit(1);  
	} 
  }
   
  

}