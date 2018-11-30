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
#include <vtkCubeSource.h>
#include <vtkProperty.h>
#include <vtkTriangleFilter.h>
#include <vtkMassProperties.h>

int main(int argc, char* argv[])
{
//    if(argc < 2)
//    {
//        std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
//        return EXIT_FAILURE;
//    }

    vtkSmartPointer<vtkCubeSource> cubeSource =
            vtkSmartPointer<vtkCubeSource>::New();
    cubeSource->Update();

    vtkSmartPointer<vtkTriangleFilter> triFilter =
            vtkSmartPointer<vtkTriangleFilter>::New();
    triFilter->SetInputData(cubeSource->GetOutput());
    triFilter->Update();

    vtkSmartPointer<vtkMassProperties> massProp =
            vtkSmartPointer<vtkMassProperties>::New();
    massProp->SetInputData(triFilter->GetOutput());
    float vol = massProp->GetVolume();
    float area = massProp->GetSurfaceArea();
    float maxArea = massProp->GetMaxCellArea();
    float minArea = massProp->GetMinCellArea();

    std::cout<<"Volume      :"<<vol<<std::endl;
    std::cout<<"Surface Area:"<<area<<std::endl;
    std::cout<<"Max Area    :"<<maxArea<<std::endl;
    std::cout<<"Min Area    :"<<minArea<<std::endl;

    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputData(triFilter->GetOutput());
    mapper->SetInputConnection(cubeSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor =
            vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0,1,0);
    actor->GetProperty()->SetEdgeColor(1,0,0);
    actor->GetProperty()->SetEdgeVisibility(1);

    vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();
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
