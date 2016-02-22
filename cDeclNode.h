#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
// 
// Modified By: Mark Shanklin
// mark.shanklin@oit.edu
//
// Mod Date: Feb. 21, 2016
//

#include "cAstNode.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode() {}
        virtual bool isVar(){ return false; }
        virtual bool isStruct(){ return false; }
        virtual bool isFloat(){ return false; }
        virtual bool isInt(){ return false; }
        virtual string GetName(){ return nullptr; }        
        virtual int GetSize() = 0;
        virtual cDeclNode* GetType() = 0;
};
