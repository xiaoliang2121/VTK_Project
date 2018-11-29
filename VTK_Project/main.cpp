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

#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>

int main(int argc, char* argv[])
{
//    if(argc < 2)
//    {
//        std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
//        return EXIT_FAILURE;
//    }

    vtkSmartPointer<vtkImageData> img =
            vtkSmartPointer<vtkImageData>::New();
    img->SetDimensions(16,16,1);
    img->AllocateScalars(VTK_UNSIGNED_CHAR,1);

    unsigned char *ptr = (unsigned char*)img->GetScalarPointer();
    for(int i=0; i<16*16*1; i++)
        *ptr++ = i%256;

    vtkSmartPointer<vtkImageActor> redActor =
            vtkSmartPointer<vtkImageActor>::New();
    redActor->SetInputData(img);

    double redViewport[4] = {0.0, 0.0, 1.0, 1.0};
    vtkSmartPointer<vtkRenderer> redRenderer =
            vtkSmartPointer<vtkRenderer>::New();
    redRenderer->SetViewport(redViewport);
    redRenderer->AddActor(redActor);
    redRenderer->ResetCamera();
    redRenderer->SetBackground(1.0,1.0,1.0);

    // Setup render window
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(redRenderer);
    renderWindow->SetSize( 800, 600 );
    renderWindow->Render();
    renderWindow->SetWindowName("CreateVTKImageData");

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
