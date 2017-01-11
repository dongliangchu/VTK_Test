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


int main ( int argc, char *argv[] )
{
  // Ensure a filename was specified
  if(argc != 3)
    {
    std::cerr << "Usage: " << argv[0] << " InputFilename" << " OutputFilename " <<endl;
    return EXIT_FAILURE;
    }
  vtkIndent vtkdent;
  // Get the filename from the command line
  std::string inputFilename = argv[1];
  std::string outputFilename = argv[2];
  // Get all data from the file
  vtkSmartPointer<vtkDataSetReader> reader = vtkSmartPointer<vtkDataSetReader>::New();
  vtkSmartPointer<vtkDataSetWriter> Writer =vtkSmartPointer<vtkDataSetWriter>::New();
  vtkSmartPointer<vtkImageData> Altered_ImageData =vtkSmartPointer<vtkImageData>::New();
  vtkSmartPointer<vtkPoints> Origi_Points =vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkDoubleArray> Points_Array=vtkSmartPointer<vtkDoubleArray>::New();
  vtkSmartPointer<vtkPointData> Points_Data =vtkSmartPointer<vtkPointData>::New();
  vtkSmartPointer<vtkRectilinearGrid> Origi_Rectilinear =vtkSmartPointer<vtkRectilinearGrid>::New(); 
  
  
  reader->SetFileName(inputFilename.c_str());
  reader->Update(); 

  Origi_Rectilinear=reader->GetRectilinearGridOutput();
  //Origi_Rectilinear->PrintSelf(std::cout,vtkdent);
  Origi_Rectilinear->GetPoints((vtkPoints*) Origi_Points);

  vtkIdType point_num=Origi_Points->GetNumberOfPoints();
  Points_Data =Origi_Rectilinear->GetPointData();
 
  double bound[6];
  Origi_Points->GetBounds(bound);
  Altered_ImageData->SetOrigin(bound[0],bound[2],bound[4]);
 
  int dimension[3];
  Origi_Rectilinear->GetDimensions(dimension);
  Altered_ImageData->SetDimensions(dimension);

  double xspacing, yspacing,zspacing;
  xspacing=(bound[1]-bound[0])/dimension[0];
  yspacing=(bound[3]-bound[2])/dimension[1];
  zspacing=(bound[5]-bound[4])/dimension[2];
  Altered_ImageData->SetSpacing(xspacing,yspacing,zspacing);
  

  vtkIdType ScalarTuNum=0, VectorTuNum=0;
  if(Points_Data->GetScalars())
  {
    ScalarTuNum=Points_Data->GetScalars()->GetNumberOfTuples();
    Altered_ImageData->GetPointData()->SetScalars(Points_Data->GetScalars());  
  } 
  if(Points_Data->GetVectors())
  {
   VectorTuNum=Points_Data->GetVectors()->GetNumberOfTuples();
   Altered_ImageData->GetPointData()->SetVectors(Points_Data->GetVectors());  
  }
 
 
  std::cout<<"image data print "<<"  \n";
  Altered_ImageData->PrintSelf(std::cout,vtkdent); 
                               
  Writer->SetFileName(outputFilename.c_str());
  Writer->SetInputData((vtkDataObject *)Altered_ImageData);
  Writer->Write(); 
   
  
  return EXIT_SUCCESS;
}
