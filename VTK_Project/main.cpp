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

#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <iostream>

int main(int argc, char* argv[])
{
//    if(argc < 2)
//    {
//        std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
//        return EXIT_FAILURE;
//    }

    vtkSmartPointer<vtkConeSource> coneSrc =
            vtkSmartPointer<vtkConeSource>::New();
    coneSrc->Update();

    vtkSmartPointer<vtkPolyData> cone = coneSrc->GetOutput();
    int nPoints = cone->GetNumberOfPoints();
    int nCells = cone->GetNumberOfCells();

    std::cout<<"Points number:"<<nPoints<<std::endl;
    std::cout<<"Cells  number:"<<nCells<<std::endl;

    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(cone);

    vtkSmartPointer<vtkActor> actor =
            vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

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
    renderWindow->SetWindowName("PolyDataSource");

    // Setup render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();

    // Render and start interaction
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
