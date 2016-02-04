#pragma once
/*******************************************
 * cBinaryExprNode.h
 *
 * Defines an AST node for an Binary ...
 *
 * Inherits from cExprNode so that the Binary Expr constants can be used anywhere
 *
 * expressions are used.
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02 2016
 ******************************************/

#include "cAstNode.h"
#include "cExprNode.h"

class cBinaryExprNode : public cExprNode
{
    public:
        //param1 is the pointer of the first child node.
        //param2 is the char of the binary operator.
        //param3 is the pointer of the second child node.
        cBinaryExprNode(cExprNode *childOne, char binaryOp, cExprNode *childTwo) : cExprNode()
        {
            AddChild(childOne);

            cOpNode *op = new cOpNode(binaryOp);
            
            AddChild(op);

            AddChild(childTwo);
        }
        virtual string NodeType() { return string("expr");}
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
