#pragma once
/*******************************************
 * cParamsNode.h
 *
 * Author:Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date:Feb. 03, 2016
 ******************************************/

#include "cAstNode.h"
#include "cDeclNode.h"

class cParamsNode : public cDeclNode
{
    public:
        cParamsNode(cDeclNode *args)
        {
            AddChild(args);
        }
        void Insert(cDeclNode *params)
        {
            AddChild(params);
        }
        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
