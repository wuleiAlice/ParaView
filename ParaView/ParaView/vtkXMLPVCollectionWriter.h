/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkXMLPVCollectionWriter.h
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
// .NAME vtkXMLPVCollectionWriter - Data writer for ParaView
// .SECTION Description
// vtkXMLPVCollectionWriter is used to save all parts of a current
// source to a file with pieces spread across ther server processes.

#ifndef __vtkXMLPVCollectionWriter_h
#define __vtkXMLPVCollectionWriter_h

#include "vtkXMLWriter.h"

class vtkXMLPVCollectionWriterInternals;

class VTK_IO_EXPORT vtkXMLPVCollectionWriter : public vtkXMLWriter
{
public:
  static vtkXMLPVCollectionWriter* New();
  vtkTypeRevisionMacro(vtkXMLPVCollectionWriter,vtkXMLWriter);
  void PrintSelf(ostream& os, vtkIndent indent);  
  
  // Description:
  // Get the default file extension for files written by this writer.
  virtual const char* GetDefaultFileExtension();
  
  // Description:
  // Add the given data set as an input.
  void AddInput(vtkDataSet* ds);
  
  // Description:
  // Get/Set the piece number to write.  The same piece number is used
  // for all inputs.
  vtkGetMacro(Piece, int);
  vtkSetMacro(Piece, int);
  
  // Description:
  // Get/Set the number of pieces into which the inputs are split.
  vtkGetMacro(NumberOfPieces, int);
  vtkSetMacro(NumberOfPieces, int);
  
  // Description:
  // Get/Set whether this instance will write the main collection
  // file.
  vtkGetMacro(WriteCollectionFile, int);
  virtual void SetWriteCollectionFile(int flag);
protected:
  vtkXMLPVCollectionWriter();
  ~vtkXMLPVCollectionWriter();
  
  // Replace vtkXMLWriter's writing driver method.
  virtual int WriteInternal();
  virtual int WriteData();
  virtual const char* GetDataSetName();
  
  // Create the set of writers matching the set of inputs.
  void CreateWriters();
  
  // Split the prefix off the file name for use in creating other file
  // names.
  void SplitFileName();
  
  // Internal implementation details.
  vtkXMLPVCollectionWriterInternals* Internal;  
  
  // The piece number to write.
  int Piece;
  
  // The number of pieces into which the inputs are split.
  int NumberOfPieces;
  
  // Whether to write the collection file on this node.
  int WriteCollectionFile;
  int WriteCollectionFileInitialized;
  
private:
  vtkXMLPVCollectionWriter(const vtkXMLPVCollectionWriter&);  // Not implemented.
  void operator=(const vtkXMLPVCollectionWriter&);  // Not implemented.
};

#endif
