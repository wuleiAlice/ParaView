/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkXMLPVCollectionWriter.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkXMLPVCollectionWriter.h"

#include "vtkImageData.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"
#include "vtkRectilinearGrid.h"
#include "vtkSmartPointer.h"
#include "vtkStructuredGrid.h"
#include "vtkUnstructuredGrid.h"
#include "vtkXMLImageDataWriter.h"
#include "vtkXMLPDataWriter.h"
#include "vtkXMLPImageDataWriter.h"
#include "vtkXMLPPolyDataWriter.h"
#include "vtkXMLPRectilinearGridWriter.h"
#include "vtkXMLPStructuredGridWriter.h"
#include "vtkXMLPUnstructuredGridWriter.h"
#include "vtkXMLPolyDataWriter.h"
#include "vtkXMLRectilinearGridWriter.h"
#include "vtkXMLStructuredGridWriter.h"
#include "vtkXMLUnstructuredGridWriter.h"
#include "vtkXMLWriter.h"

#include <vtkstd/string>
#include <vtkstd/vector>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkXMLPVCollectionWriter);
vtkCxxRevisionMacro(vtkXMLPVCollectionWriter, "1.1");

class vtkXMLPVCollectionWriterInternals
{
public:
  vtkstd::vector< vtkSmartPointer<vtkXMLWriter> > Writers;
  vtkstd::string FilePrefix;
  vtkstd::string CreatePieceFileName(int index);
};

//----------------------------------------------------------------------------
vtkXMLPVCollectionWriter::vtkXMLPVCollectionWriter()
{
  this->Internal = new vtkXMLPVCollectionWriterInternals;
  this->Piece = 0;
  this->NumberOfPieces = 1;
  this->WriteCollectionFileInitialized = 0;
  this->WriteCollectionFile = 0;
}

//----------------------------------------------------------------------------
vtkXMLPVCollectionWriter::~vtkXMLPVCollectionWriter()
{
  delete this->Internal;
}

//----------------------------------------------------------------------------
void vtkXMLPVCollectionWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
void vtkXMLPVCollectionWriter::AddInput(vtkDataSet* ds)
{
  this->vtkProcessObject::AddInput(ds);
}

//----------------------------------------------------------------------------
void vtkXMLPVCollectionWriter::SetWriteCollectionFile(int flag)
{
  this->WriteCollectionFileInitialized = 1;
  vtkDebugMacro(<< this->GetClassName() << " ("
                << this << "): setting WriteCollectionFile to " << flag);
  if(this->WriteCollectionFile != flag)
    {
    this->WriteCollectionFile = flag;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
int vtkXMLPVCollectionWriter::WriteInternal()
{
  // Prepare file prefix for creation of internal file names.
  this->SplitFileName();
  
  // Create writers for each input.
  this->CreateWriters();
  
  // Write each input.
  int i;
  for(i=0; i < this->GetNumberOfInputs(); ++i)
    {
    if(this->Internal->Writers[i].GetPointer())
      {
      vtkstd::string fname = this->Internal->CreatePieceFileName(i);
      this->Internal->Writers[i]->SetFileName(fname.c_str());
      this->Internal->Writers[i]->Write();
      }
    }
  
  // Decide whether to write the collection file.
  int writeCollection = 0;
  if(this->WriteCollectionFileInitialized)
    {
    writeCollection = this->WriteCollectionFile;
    }
  else if(this->Piece == 0)
    {
    writeCollection = 1;
    }
  
  // Write the collection file if requested.
  if(writeCollection)
    {
    if(!this->Superclass::WriteInternal()) { return 0; }
    }
  
  return 1;  
}

//----------------------------------------------------------------------------
int vtkXMLPVCollectionWriter::WriteData()
{
  // Write the collection file.
  this->StartFile();
  vtkIndent indent = vtkIndent().GetNextIndent();
  
  // Open the primary element.
  ostream& os = *(this->Stream);
  os << indent << "<" << this->GetDataSetName() << ">\n";
  
  // Write a DataSet entry for each input that was written.
  int i;
  for(i=0; i < this->GetNumberOfInputs(); ++i)
    {
    if(this->Internal->Writers[i].GetPointer())
      {
      vtkstd::string fname = this->Internal->CreatePieceFileName(i);
      os << indent.GetNextIndent()
         << "<DataSet part=\"" << i << "\" file=\""
         << fname.c_str() << "\"/>\n";
      }
    }
  
  // Close the primary element.
  os << indent << "</" << this->GetDataSetName() << ">\n";
  this->EndFile();
  
  return 1;
}

//----------------------------------------------------------------------------
const char* vtkXMLPVCollectionWriter::GetDefaultFileExtension()
{
  return "vtc";
}

//----------------------------------------------------------------------------
const char* vtkXMLPVCollectionWriter::GetDataSetName()
{
  return "Collection";
}

//----------------------------------------------------------------------------
void vtkXMLPVCollectionWriter::CreateWriters()
{
  int i;
  this->Internal->Writers.resize(this->GetNumberOfInputs());
  for(i=0; i < this->GetNumberOfInputs(); ++i)
    {
    // Create a writer based on the type of this input.
    switch (this->Inputs[i]->GetDataObjectType())
      {
      case VTK_POLY_DATA:    
        if(this->NumberOfPieces > 1)
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLPPolyDataWriter") != 0))
            {
            vtkXMLPPolyDataWriter* w = vtkXMLPPolyDataWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLPPolyDataWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkPolyData::SafeDownCast(this->Inputs[i]));
          }
        else
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLPolyDataWriter") != 0))
            {
            vtkXMLPolyDataWriter* w = vtkXMLPolyDataWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLPolyDataWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkPolyData::SafeDownCast(this->Inputs[i]));
          }
        break;
      case VTK_STRUCTURED_POINTS:
      case VTK_IMAGE_DATA:
        if(this->NumberOfPieces > 1)
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLPImageDataWriter") != 0))
            {
            vtkXMLPImageDataWriter* w = vtkXMLPImageDataWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLPImageDataWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkImageData::SafeDownCast(this->Inputs[i]));
          }
        else
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLImageDataWriter") != 0))
            {
            vtkXMLImageDataWriter* w = vtkXMLImageDataWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLImageDataWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkImageData::SafeDownCast(this->Inputs[i]));
          }
        break;
      case VTK_UNSTRUCTURED_GRID:
        if(this->NumberOfPieces > 1)
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLPUnstructuredGridWriter") != 0))
            {
            vtkXMLPUnstructuredGridWriter* w = vtkXMLPUnstructuredGridWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLPUnstructuredGridWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkUnstructuredGrid::SafeDownCast(this->Inputs[i]));
          }
        else
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLUnstructuredGridWriter") != 0))
            {
            vtkXMLUnstructuredGridWriter* w = vtkXMLUnstructuredGridWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLUnstructuredGridWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkUnstructuredGrid::SafeDownCast(this->Inputs[i]));
          }
        break;
      case VTK_STRUCTURED_GRID:
        if(this->NumberOfPieces > 1)
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLPStructuredGridWriter") != 0))
            {
            vtkXMLPStructuredGridWriter* w = vtkXMLPStructuredGridWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLPStructuredGridWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkStructuredGrid::SafeDownCast(this->Inputs[i]));
          }
        else
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLStructuredGridWriter") != 0))
            {
            vtkXMLStructuredGridWriter* w = vtkXMLStructuredGridWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLStructuredGridWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkStructuredGrid::SafeDownCast(this->Inputs[i]));
          }
        break;
      case VTK_RECTILINEAR_GRID:
        if(this->NumberOfPieces > 1)
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLPRectilinearGridWriter") != 0))
            {
            vtkXMLPRectilinearGridWriter* w = vtkXMLPRectilinearGridWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLPRectilinearGridWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkRectilinearGrid::SafeDownCast(this->Inputs[i]));
          }
        else
          {
          if(!this->Internal->Writers[i].GetPointer() ||
             (strcmp(this->Internal->Writers[i]->GetClassName(),
                     "vtkXMLRectilinearGridWriter") != 0))
            {
            vtkXMLRectilinearGridWriter* w = vtkXMLRectilinearGridWriter::New();
            this->Internal->Writers[i] = w;
            w->Delete();
            }
          vtkXMLRectilinearGridWriter::SafeDownCast(this->Internal->Writers[i].GetPointer())
            ->SetInput(vtkRectilinearGrid::SafeDownCast(this->Inputs[i]));
          }
        break;
      }
    
    // If this is a parallel writer, set the piece information.
    if(vtkXMLPDataWriter* w = vtkXMLPDataWriter::SafeDownCast(this->Internal->Writers[i].GetPointer()))
      {
      w->SetStartPiece(this->Piece);
      w->SetEndPiece(this->Piece);
      w->SetNumberOfPieces(this->NumberOfPieces);
      w->SetGhostLevel(0);
      }
    }
}

//----------------------------------------------------------------------------
void vtkXMLPVCollectionWriter::SplitFileName()
{
  // Set the prefix for output file names.
  this->Internal->FilePrefix = this->FileName;
  vtkstd::string::size_type pos = this->Internal->FilePrefix.find_last_of(".");
  if(pos != vtkstd::string::npos)
    {
    this->Internal->FilePrefix = this->Internal->FilePrefix.substr(0, pos);
    }
}

//----------------------------------------------------------------------------
vtkstd::string
vtkXMLPVCollectionWriterInternals::CreatePieceFileName(int index)
{
  vtkstd::string fname;
  ostrstream fn_with_warning_C4701;
  fn_with_warning_C4701
    << this->FilePrefix.c_str() << "_" << index << "."
    << this->Writers[index]->GetDefaultFileExtension() << ends;
  fname = fn_with_warning_C4701.str();
  fn_with_warning_C4701.rdbuf()->freeze(0);
  return fname;
}
