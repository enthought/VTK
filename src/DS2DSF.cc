/*=========================================================================

  Program:   Visualization Library
  Module:    DS2DSF.cc
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

This file is part of the Visualization Library. No part of this file or its 
contents may be copied, reproduced or altered in any way without the express
written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
#include "DS2DSF.hh"
#include "PolyData.hh"

vlDataSetToDataSetFilter::vlDataSetToDataSetFilter()
{
  // prevents dangling reference to DataSet
  this->DataSet = new vlPolyData;
}

vlDataSetToDataSetFilter::~vlDataSetToDataSetFilter()
{
  delete this->DataSet;
}

void vlDataSetToDataSetFilter::Update()
{
  vlDataSetFilter::Update();
}

// Description:
// Initialize method is fancy: creates an internal dataset that holds
// geometry representation. All methods directed at geometry are 
// forwarded to internal dataset.
void vlDataSetToDataSetFilter::Initialize()
{
  if ( this->Input )
    {
    delete this->DataSet;
    // copies input geometry to internal data set
    this->DataSet = this->Input->MakeObject(); 
    }
  else
    {
    return;
    }
}

void vlDataSetToDataSetFilter::ComputeBounds()
{
  float *bounds = this->DataSet->GetBounds();
  for (int i=0; i<6; i++) this->Bounds[i] = bounds[i];
}

void vlDataSetToDataSetFilter::PrintSelf(ostream& os, vlIndent indent)
{
  if (this->ShouldIPrint(vlDataSetToDataSetFilter::GetClassName()))
    {
    this->PrintWatchOn(); // watch for multiple inheritance

    vlDataSet::PrintSelf(os,indent);
    vlDataSetFilter::PrintSelf(os,indent);

    if ( this->DataSet )
      {
      os << indent << "DataSet: (" << this->DataSet << ")\n";
      os << indent << "DataSet type: " << this->DataSet->GetClassName() << "\n";
      }
    else
      {
      os << indent << "DataSet: (none)\n";
      }

    this->PrintWatchOff(); // stop worrying about it now
   }
}
