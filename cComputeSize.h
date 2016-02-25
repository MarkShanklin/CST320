#pragma once
/*******************************************
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 *
 * Date: Feb. 23, 2016
 ******************************************/
#include "cVisitor.h"

class cComputeSize : public cVisitor
{
    public:
        cComputeSize() : cVisitor()
        {
            m_offset = 0;
            m_highWater = m_offset;
        }

        virtual void VisitAllNodes(cAstNode* node) { node->Visit(this); }

        int GetHighWater() { return m_highWater; }

        virtual void Visit(cBlockNode* node)
        {
            int startPoint = m_offset;
            int highWater = m_highWater;
            m_highWater = 0;
            
            VisitAllChildren(node);

            node->SetSize(m_highWater - startPoint);
            m_highWater = std::max(highWater, m_highWater);
            m_offset = startPoint;
            if(m_highWater < m_offset){m_highWater = m_offset;}
        }

        virtual void Visit(cDeclsNode* node)
        {
            int startPoint = m_offset;
            VisitAllChildren(node);
            node->SetSize(m_offset - startPoint);
        }

        virtual void Visit(cVarDeclNode* node)
        {
            int size;
            if(node->GetType()->IsStruct()){size = node->GetType()->GetSize();}
            else{size = node->GetType()->Sizeof();}
            node->SetSize(size);
            if(size > 1){m_offset = WordAlign(m_offset);}
            node->SetOffset(m_offset);
            m_offset += size;
            if(m_highWater < m_offset){m_highWater = m_offset;}
        }

        virtual void Visit(cStructDeclNode* node)
        {
            int startPoint = m_offset;
            m_offset = 0;
            VisitAllChildren(node);
            node->SetSize(m_offset);
            m_offset = startPoint;
        }

    protected:
        int m_offset;
        int m_highWater;

        int WordAlign (int value)
        {  
           if(value%4 != 0) 
            value += 4 - value%4;

            return value;
        }
};
