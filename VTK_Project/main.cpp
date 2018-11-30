/**********************************************************************

  文件名: 2.1_RenderCylinder.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkPointData.h>
#include <vtkActor.h>
#include <vtkScalarBarActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkTriangleFilter.h>
#include <vtkMassProperties.h>
#include <vtkDijkstraGraphGeodesicPath.h>

int main(int argc, char* argv[])
{
//    if(argc < 2)
//    {
//        std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
//        return EXIT_FAILURE;
//    }

    vtkSmartPointer<vtkSphereSource> sphereSource =
            vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    vtkSmartPointer<vtkDijkstraGraphGeodesicPath> dijkstra =
            vtkSmartPointer<vtkDijkstraGraphGeodesicPath>::New();
    dijkstra->SetInputData(sphereSource->GetOutput());
    dijkstra->SetStartVertex(0);
    dijkstra->SetEndVertex(10);
    dijkstra->Update();

//    vtkSmartPointer<vtkMassProperties> massProp =
//            vtkSmartPointer<vtkMassProperties>::New();
//    massProp->SetInputData(triFilter->GetOutput());
//    float vol = massProp->GetVolume();
//    float area = massProp->GetSurfaceArea();
//    float maxArea = massProp->GetMaxCellArea();
//    float minArea = massProp->GetMinCellArea();

//    std::cout<<"Volume      :"<<vol<<std::endl;
//    std::cout<<"Surface Area:"<<area<<std::endl;
//    std::cout<<"Max Area    :"<<maxArea<<std::endl;
//    std::cout<<"Min Area    :"<<minArea<<std::endl;

    vtkSmartPointer<vtkPolyDataMapper> pathMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    pathMapper->SetInputData(dijkstra->GetOutput());
//    mapper->SetInputConnection(cubeSource->GetOutputPort());

    vtkSmartPointer<vtkActor> pathActor =
            vtkSmartPointer<vtkActor>::New();
    pathActor->SetMapper(pathMapper);
    pathActor->GetProperty()->SetColor(1,0,0);
    pathActor->GetProperty()->SetLineWidth(4);

    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(sphereSource->GetOutput());

    vtkSmartPointer<vtkActor> actor =
            vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(pathActor);
    renderer->AddActor(actor);
    renderer->SetBackground(1.0,1.0,1.0);

    // Setup render window
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize( 800, 600 );
    renderWindow->Render();
    renderWindow->SetWindowName("PolyDataMassProperty");

    // Setup render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    // Render and start interaction
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
