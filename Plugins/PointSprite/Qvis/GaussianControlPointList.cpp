/*****************************************************************************
*
* Copyright (c) 2000 - 2007, The Regents of the University of California
* Produced at the Lawrence Livermore National Laboratory
* All rights reserved.
*
* This file is part of VisIt. For details, see http://www.llnl.gov/visit/. The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or materials provided with the distribution.
*  - Neither the name of the UC/LLNL nor  the names of its contributors may be
*    used to  endorse or  promote products derived from  this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
* CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
* ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#include <DataNode.h>
#include <GaussianControlPoint.h>
#include <GaussianControlPointList.h>

namespace pointsprite
{
// Type map format string
const char* GaussianControlPointList::TypeMapFormatString = "a*";

// ****************************************************************************
// Method: GaussianControlPointList::GaussianControlPointList
//
// Purpose:
//   Constructor for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

GaussianControlPointList::GaussianControlPointList()
  : AttributeSubject(GaussianControlPointList::TypeMapFormatString)
{
}

// ****************************************************************************
// Method: GaussianControlPointList::GaussianControlPointList
//
// Purpose:
//   Copy constructor for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

GaussianControlPointList::GaussianControlPointList(const GaussianControlPointList& obj)
  : AttributeSubject(GaussianControlPointList::TypeMapFormatString)
{
  AttributeGroupVector::const_iterator pos;

  // *** Copy the controlPoints field ***
  // Delete the AttributeGroup objects and clear the vector.
  for (pos = controlPoints.begin(); pos != controlPoints.end(); ++pos)
    delete *pos;
  controlPoints.clear();
  if (obj.controlPoints.size() > 0)
    controlPoints.reserve(obj.controlPoints.size());
  // Duplicate the controlPoints from obj.
  for (pos = obj.controlPoints.begin(); pos != obj.controlPoints.end(); ++pos)
  {
    GaussianControlPoint* oldGaussianControlPoint = (GaussianControlPoint*)(*pos);
    GaussianControlPoint* newGaussianControlPoint =
      new GaussianControlPoint(*oldGaussianControlPoint);
    controlPoints.push_back(newGaussianControlPoint);
  }

  SelectAll();
}

// ****************************************************************************
// Method: GaussianControlPointList::~GaussianControlPointList
//
// Purpose:
//   Destructor for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

GaussianControlPointList::~GaussianControlPointList()
{
  AttributeGroupVector::iterator pos;

  // Destroy the controlPoints field.
  for (pos = controlPoints.begin(); pos != controlPoints.end(); ++pos)
    delete *pos;
}

// ****************************************************************************
// Method: GaussianControlPointList::operator =
//
// Purpose:
//   Assignment operator for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

GaussianControlPointList& GaussianControlPointList::operator=(const GaussianControlPointList& obj)
{
  if (this == &obj)
    return *this;
  AttributeGroupVector::const_iterator pos;

  // *** Copy the controlPoints field ***
  // Delete the AttributeGroup objects and clear the vector.
  for (pos = controlPoints.begin(); pos != controlPoints.end(); ++pos)
    delete *pos;
  controlPoints.clear();
  if (obj.controlPoints.size() > 0)
    controlPoints.reserve(obj.controlPoints.size());
  // Duplicate the controlPoints from obj.
  for (pos = obj.controlPoints.begin(); pos != obj.controlPoints.end(); ++pos)
  {
    GaussianControlPoint* oldGaussianControlPoint = (GaussianControlPoint*)(*pos);
    GaussianControlPoint* newGaussianControlPoint =
      new GaussianControlPoint(*oldGaussianControlPoint);
    controlPoints.push_back(newGaussianControlPoint);
  }

  SelectAll();
  return *this;
}

// ****************************************************************************
// Method: GaussianControlPointList::operator ==
//
// Purpose:
//   Comparison operator == for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

bool GaussianControlPointList::operator==(const GaussianControlPointList& obj) const
{
  unsigned int i;

  bool controlPoints_equal = (obj.controlPoints.size() == controlPoints.size());
  for (i = 0; (i < controlPoints.size()) && controlPoints_equal; ++i)
  {
    // Make references to GaussianControlPoint from AttributeGroup *.
    const GaussianControlPoint& controlPoints1 = *((const GaussianControlPoint*)(controlPoints[i]));
    const GaussianControlPoint& controlPoints2 =
      *((const GaussianControlPoint*)(obj.controlPoints[i]));
    controlPoints_equal = (controlPoints1 == controlPoints2);
  }

  // Create the return value
  return (controlPoints_equal);
}

// ****************************************************************************
// Method: GaussianControlPointList::operator !=
//
// Purpose:
//   Comparison operator != for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

bool GaussianControlPointList::operator!=(const GaussianControlPointList& obj) const
{
  return !(this->operator==(obj));
}

// ****************************************************************************
// Method: GaussianControlPointList::TypeName
//
// Purpose:
//   Type name method for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

const std::string GaussianControlPointList::TypeName() const
{
  return "GaussianControlPointList";
}

// ****************************************************************************
// Method: GaussianControlPointList::CopyAttributes
//
// Purpose:
//   CopyAttributes method for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

bool GaussianControlPointList::CopyAttributes(const AttributeGroup* atts)
{
  if (TypeName() != atts->TypeName())
    return false;

  // Call assignment operator.
  const GaussianControlPointList* tmp = (const GaussianControlPointList*)atts;
  *this = *tmp;

  return true;
}

// ****************************************************************************
// Method: GaussianControlPointList::CreateCompatible
//
// Purpose:
//   CreateCompatible method for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

AttributeSubject* GaussianControlPointList::CreateCompatible(const std::string& tname) const
{
  AttributeSubject* retval = 0;
  if (TypeName() == tname)
    retval = new GaussianControlPointList(*this);
  // Other cases could go here too.

  return retval;
}

// ****************************************************************************
// Method: GaussianControlPointList::NewInstance
//
// Purpose:
//   NewInstance method for the GaussianControlPointList class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

AttributeSubject* GaussianControlPointList::NewInstance(bool copy) const
{
  AttributeSubject* retval = 0;
  if (copy)
    retval = new GaussianControlPointList(*this);
  else
    retval = new GaussianControlPointList;

  return retval;
}

// ****************************************************************************
// Method: GaussianControlPointList::SelectAll
//
// Purpose:
//   Selects all attributes.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

void GaussianControlPointList::SelectAll()
{
  Select(0, (void*)&controlPoints);
}

// ****************************************************************************
// Method: GaussianControlPointList::CreateSubAttributeGroup
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

AttributeGroup* GaussianControlPointList::CreateSubAttributeGroup(int)
{
  return new GaussianControlPoint;
}

///////////////////////////////////////////////////////////////////////////////
// Persistence methods
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: GaussianControlPointList::CreateNode
//
// Purpose:
//   This method creates a DataNode representation of the object so it can be saved to a config
//   file.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

bool GaussianControlPointList::CreateNode(DataNode* parentNode, bool completeSave, bool forceAdd)
{
  if (parentNode == 0)
    return false;

  GaussianControlPointList defaultObject;
  bool addToParent = false;
  // Create a node for GaussianControlPointList.
  DataNode* node = new DataNode("GaussianControlPointList");

  if (completeSave || !FieldsEqual(0, &defaultObject))
  {
    addToParent = true;
    for (unsigned int i = 0; i < controlPoints.size(); ++i)
      controlPoints[i]->CreateNode(node, completeSave, true);
  }

  // Add the node to the parent node.
  if (addToParent || forceAdd)
    parentNode->AddNode(node);
  else
    delete node;

  return (addToParent || forceAdd);
}

// ****************************************************************************
// Method: GaussianControlPointList::SetFromNode
//
// Purpose:
//   This method sets attributes in this object from values in a DataNode representation of the
//   object.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

void GaussianControlPointList::SetFromNode(DataNode* parentNode)
{
  int i;
  if (parentNode == 0)
    return;

  DataNode* searchNode = parentNode->GetNode("GaussianControlPointList");
  if (searchNode == 0)
    return;

  // DataNode *node;
  DataNode** children;
  // Clear all the GaussianControlPoints.
  ClearControlPoints();

  // Go through all of the children and construct a new
  // GaussianControlPoint for each one of them.
  children = searchNode->GetChildren();
  for (i = 0; i < searchNode->GetNumChildren(); ++i)
  {
    if (children[i]->GetKey() == std::string("GaussianControlPoint"))
    {
      GaussianControlPoint temp;
      temp.SetFromNode(children[i]);
      AddControlPoints(temp);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// Set property methods
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Get property methods
///////////////////////////////////////////////////////////////////////////////

const AttributeGroupVector& GaussianControlPointList::GetControlPoints() const
{
  return controlPoints;
}

AttributeGroupVector& GaussianControlPointList::GetControlPoints()
{
  return controlPoints;
}

///////////////////////////////////////////////////////////////////////////////
// Select property methods
///////////////////////////////////////////////////////////////////////////////

void GaussianControlPointList::SelectControlPoints()
{
  Select(0, (void*)&controlPoints);
}

///////////////////////////////////////////////////////////////////////////////
// AttributeGroupVector convenience methods.
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: GaussianControlPointList::AddControlPoints
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

void GaussianControlPointList::AddControlPoints(const GaussianControlPoint& obj)
{
  GaussianControlPoint* newGaussianControlPoint = new GaussianControlPoint(obj);
  controlPoints.push_back(newGaussianControlPoint);

  // Indicate that things have changed by selecting it.
  Select(0, (void*)&controlPoints);
}

// ****************************************************************************
// Method: GaussianControlPointList::ClearControlPoints
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

void GaussianControlPointList::ClearControlPoints()
{
  AttributeGroupVector::iterator pos;

  for (pos = controlPoints.begin(); pos != controlPoints.end(); ++pos)
    delete *pos;
  controlPoints.clear();

  // Indicate that things have changed by selecting the list.
  Select(0, (void*)&controlPoints);
}

// ****************************************************************************
// Method: GaussianControlPointList::RemoveControlPoints
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

void GaussianControlPointList::RemoveControlPoints(int index)
{
  AttributeGroupVector::iterator pos = controlPoints.begin();

  // Iterate through the vector "index" times.
  for (int i = 0; i < index; ++i)
    ++pos;

  // If pos is still a valid iterator, remove that element.
  if (pos != controlPoints.end())
  {
    delete *pos;
    controlPoints.erase(pos);
  }

  // Indicate that things have changed by selecting the list.
  Select(0, (void*)&controlPoints);
}

// ****************************************************************************
// Method: GaussianControlPointList::GetNumControlPoints
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

int GaussianControlPointList::GetNumControlPoints() const
{
  return static_cast<int>(controlPoints.size());
}

// ****************************************************************************
// Method: GaussianControlPointList::GetControlPoints
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

GaussianControlPoint& GaussianControlPointList::GetControlPoints(int i)
{
  return *((GaussianControlPoint*)controlPoints[i]);
}

// ****************************************************************************
// Method: GaussianControlPointList::GetControlPoints
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

const GaussianControlPoint& GaussianControlPointList::GetControlPoints(int i) const
{
  return *((GaussianControlPoint*)controlPoints[i]);
}

// ****************************************************************************
// Method: GaussianControlPointList::operator []
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

GaussianControlPoint& GaussianControlPointList::operator[](int i)
{
  return *((GaussianControlPoint*)controlPoints[i]);
}

// ****************************************************************************
// Method: GaussianControlPointList::operator []
//
// Purpose:
//   This class contains a list of GaussianControlPoint objects.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

const GaussianControlPoint& GaussianControlPointList::operator[](int i) const
{
  return *((GaussianControlPoint*)controlPoints[i]);
}

///////////////////////////////////////////////////////////////////////////////
// Keyframing methods
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: GaussianControlPointList::GetFieldName
//
// Purpose:
//   This method returns the name of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

std::string GaussianControlPointList::GetFieldName(int index) const
{
  switch (index)
  {
    case 0:
      return "controlPoints";
    default:
      return "invalid index";
  }
}

// ****************************************************************************
// Method: GaussianControlPointList::GetFieldType
//
// Purpose:
//   This method returns the type of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

AttributeGroup::FieldType GaussianControlPointList::GetFieldType(int index) const
{
  switch (index)
  {
    case 0:
      return AttributeGroup::FieldType_attVector;
    default:
      return AttributeGroup::FieldType_unknown;
  }
}

// ****************************************************************************
// Method: GaussianControlPointList::GetFieldTypeName
//
// Purpose:
//   This method returns the name of a field type given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

std::string GaussianControlPointList::GetFieldTypeName(int index) const
{
  switch (index)
  {
    case 0:
      return "attVector";
    default:
      return "invalid index";
  }
}

// ****************************************************************************
// Method: GaussianControlPointList::FieldsEqual
//
// Purpose:
//   This method compares two fields and return true if they are equal.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Wed Mar 14 16:10:40 PST 2007
//
// Modifications:
//
// ****************************************************************************

bool GaussianControlPointList::FieldsEqual(int index_, const AttributeGroup* rhs) const
{
  unsigned int i;

  const GaussianControlPointList& obj = *((const GaussianControlPointList*)rhs);
  bool retval = false;
  switch (index_)
  {
    case 0:
    { // new scope
      bool controlPoints_equal = (obj.controlPoints.size() == controlPoints.size());
      for (i = 0; (i < controlPoints.size()) && controlPoints_equal; ++i)
      {
        // Make references to GaussianControlPoint from AttributeGroup *.
        const GaussianControlPoint& controlPoints1 =
          *((const GaussianControlPoint*)(controlPoints[i]));
        const GaussianControlPoint& controlPoints2 =
          *((const GaussianControlPoint*)(obj.controlPoints[i]));
        controlPoints_equal = (controlPoints1 == controlPoints2);
      }

      retval = controlPoints_equal;
    }
    break;
    default:
      retval = false;
  }

  return retval;
}

///////////////////////////////////////////////////////////////////////////////
// User-defined methods.
///////////////////////////////////////////////////////////////////////////////
}
