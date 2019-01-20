#include "abstractsyntaxtree.h"
using namespace std;

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    if(root == NULL){
    	return -1;
    }else{
    	Node * subroot = root;
    	return evalhelper(subroot);
    }
}

double AbstractSyntaxTree::evalhelper(Node * & subroot) const {
	if(subroot == NULL){
		return 0;
	}
	if(subroot -> elem == "+"){
		return evalhelper(subroot -> left) + evalhelper(subroot -> right);
	}else if(subroot -> elem == "-"){
		return evalhelper(subroot -> left) - evalhelper(subroot -> right);
	}else if(subroot -> elem == "*"){
		return evalhelper(subroot -> left) * evalhelper(subroot -> right);
	}else if(subroot -> elem == "/"){
		return evalhelper(subroot -> left) / evalhelper(subroot -> right);
	}else{
		return stod(subroot -> elem);
	}
	
}

