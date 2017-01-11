
#include <vtkSmartPointer.h>
#include <vtkWriter.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetWriter.h>
#include <string>
#include <stdlib.h>
#include <vtkRectilinearGrid.h>
#include <vtkPlaneSource.h>
#include <vtkStreamTracer.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkPointSet.h>
#include <vtkMath.h>


int main ( int argc, char *argv[] )
{
  // Ensure a filename was specified
  if(argc != 5)
    {
    std::cerr << "Usage: " << argv[0] << " InputFilename" <<" Number of Seeds" <<" Propagation Length" <<" StepSize"  << endl;
    //return EXIT_FAILURE;
    }

  // Get the filename from the command line
  std::string InputFilename = argv[1];
  double NumSed = atof(argv[2]);
  double PropLength = atof(argv[3]);
  double StepSize = atof(argv[4]);
   std::string OutputFilename = (std::string)"StreamLine_"+(std::string)argv[2]+(std::string)"_"+(std::string)argv[3]+(std::string)"_"+(std::string)argv[4]+(std::string)".vtk";

  vtkSmartPointer<vtkDataSetReader> reader = vtkSmartPointer<vtkDataSetReader>::New();
  vtkSmartPointer<vtkDataSetWriter> Writer =vtkSmartPointer<vtkDataSetWriter>::New();
  vtkSmartPointer<vtkPolyData> Stream_Output =vtkSmartPointer<vtkPolyData>::New();
  vtkSmartPointer<vtkPoints> Origi_Points =vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkRectilinearGrid> Origi_Rectilinear =vtkSmartPointer<vtkRectilinearGrid>::New(); 

 
  reader->SetFileName(InputFilename.c_str());
  reader->Update();
  
  vtkSmartPointer<vtkStreamTracer> streamLine = vtkSmartPointer<vtkStreamTracer>::New();

  vtkSmartPointer<vtkPoints> Seeds_Coordi =vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkPolyData> Seeds_Set =vtkSmartPointer<vtkPolyData>::New();
  
  //unsigned int numRand = 30;

  Origi_Rectilinear=reader->GetRectilinearGridOutput();
  Origi_Rectilinear->GetPoints((vtkPoints*) Origi_Points);
  double bound[6];
  Origi_Points->GetBounds(bound);

  vtkMath::RandomSeed(time(NULL));
  for(unsigned int i = 0; i < NumSed; i++)
    {
    double x_random = vtkMath::Random(0.0,1.0);
    double y_random = vtkMath::Random(0.0,1.0);
    double z_random = vtkMath::Random(0.0,1.0);
    Seeds_Coordi->InsertNextPoint(bound[0]+ x_random*(bound[1]-bound[0]),bound[2]+y_random*(bound[3]-bound[2]),bound[4]+z_random*(bound[5]-bound[4]));
    }
  

  
  

  Seeds_Set->SetPoints(Seeds_Coordi);

  
  streamLine->SetInputData((vtkDataObject *)reader->GetOutput());
  streamLine->SetSourceData((vtkDataSet*) Seeds_Set);
  vtkIndent vtkdent;
  
  streamLine->SetMaximumPropagation(PropLength);
  streamLine->SetInitialIntegrationStep(StepSize);
  streamLine->SetIntegratorTypeToRungeKutta4();
  streamLine->SetIntegrationDirectionToForward();
  streamLine->SetComputeVorticity(1);
  streamLine->Update();

  streamLine->PrintSelf(std::cout,vtkdent);
  Writer->SetFileName(OutputFilename.c_str());
  int inputport=0;
  Writer->SetInputData(streamLine->GetOutput());
  
 //ostream*  VtkPointer=Writer->OpenVTKFile();
   //Writer->WriteDataSetData(VtkPointer, surface->GetOutput());
   Writer->Write(); 
  

  
  return EXIT_SUCCESS;
}
