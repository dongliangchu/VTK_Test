#include <vtkDataArray.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkContourFilter.h>
#include <vtkWriter.h>
#include <vtkDataSetReader.h>
#include <vtkMarchingCubes.h>
#include <vtkDataSetWriter.h>
#include <vtkImageData.h>
#include <vtkRectilinearGrid.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <string>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
  // Ensure a filename was specified
  if(argc != 3)
    {
    std::cerr << "Usage: " << argv[0] << " InputFilename" << " ISO value " <<endl;
    return EXIT_FAILURE;
    }

  std::string InputFilename = argv[1];
  double ISOVal = atof(argv[2]);
  std::string OutputFilename = (std::string)"contour_"+(std::string)argv[2]+(std::string)".vtk";
  std::cout << OutputFilename;

  vtkIndent vtkdent;
  vtkSmartPointer<vtkDataSetReader> reader = vtkSmartPointer<vtkDataSetReader>::New();
  vtkSmartPointer<vtkDataSetWriter> Writer =vtkSmartPointer<vtkDataSetWriter>::New();

  reader->SetFileName(InputFilename.c_str());
  reader->Update();
 
  vtkSmartPointer<vtkMarchingCubes> surface = vtkSmartPointer<vtkMarchingCubes>::New();
  surface->SetInputData(reader->GetOutput());
  surface->SetValue(0, ISOVal);
  surface->Update();
  
   
  Writer->SetFileName(OutputFilename.c_str());
  Writer->SetInputData(surface->GetOutput());
  Writer->Write(); 

  return EXIT_SUCCESS;
}
