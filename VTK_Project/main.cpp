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

#include <vtkBMPReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout<<argv[0]<<" "<<"ImageFile(*.bmp)"<<std::endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkBMPReader> reader =
            vtkSmartPointer<vtkBMPReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageActor> redActor =
            vtkSmartPointer<vtkImageActor>::New();
    redActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkRenderer> redRenderer =
            vtkSmartPointer<vtkRenderer>::New();
    redRenderer->AddActor(redActor);
    redRenderer->SetBackground(1.0,1.0,1.0);

    // Setup render window
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(redRenderer);
    renderWindow->SetSize( 800, 600 );
    renderWindow->Render();
    renderWindow->SetWindowName("DisplayImageExample2");

    // Setup render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style =
        vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(style);
    // Render and start interaction
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
