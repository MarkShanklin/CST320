/*******************************************
 * cOpNode.cpp
 *
 * Author: Mark Shanklin
 * mark.shanklin@oit.edu
 *
 * Date: Feb. 04, 2016
 ******************************************/

#include "lex.h"
#include "astnodes.h"
#include "cOpNode.h"
#include "langparse.h"

string cOpNode::AttributesToString()
{
    if(m_op == EQUALS)
    {
        return string(" value='") + "==" + "'";
    }
    else return string(" value='") + (char)m_op + "'";
}
