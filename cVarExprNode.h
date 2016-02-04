#pragma once
/*******************************************
 * cVarExprNode
 *
 * Defines class for variable expressions.
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 02, 2016
 ******************************************/

#include "cExprNode.h"

class cVarExprNode : public cExprNode
{
    public:
        cVarExprNode(cSymbol *name) : cExprNode()
        {
            AddChild(name);
        }
        
        void Insert(cSymbol *name)
        {
            AddChild(name);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
