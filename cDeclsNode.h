#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 28, 2015
//
// Modified By: Mark Shanklin
// mark.shanklin@oit.edu
//
// Mod Date: Feb. 26, 2016

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        // param is the first decl in this decls
        cDeclsNode(cDeclNode *decl) : cAstNode()
        {
            AddChild(decl);
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }

        cDeclNode *GetDecl(int index)
        {
            return (cDeclNode *)GetChild(index);
        }

        // return the sum of the sizes of the decls
        virtual int Sizeof()
        {
            int size = 0;

            cAstNode::iterator it;

            for (it = FirstChild(); it != LastChild(); it++)
            {
                size += dynamic_cast<cDeclNode *>(*it)->Sizeof();
            }
            return size;
        }

        virtual int GetSize()
        {
            return m_size;
        }

        virtual void SetSize(int size)
        {
            m_size = size;
        }

        // return the XML node name
        virtual string NodeType() { return string("decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual string AttributesToString()
        {
            if(m_size != 0)
                return string(" size =\"" + std::to_string(m_size) + "\"");
            else
                return string("");
        }
    protected:
        int m_size;
};
