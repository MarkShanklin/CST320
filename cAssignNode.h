#pragma once
/*******************************************
 * cAssignNode.h
 *
 * Defines AST node for assignment expressions
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02, 2016
 ******************************************/

#include "cAstNode.h"
#include "cVarExprNode.h"
#include "cExprNode.h"

class cAssignNode : public cExprNode
{
    public:
        cAssignNode(cVarExprNode *varExpr, cExprNode *expr)
        {
            AddChild(varExpr);
            AddChild(expr);
        }
    virtual string NodeType() { return string("assign"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
