﻿/**********************************************************************

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

#include <vtkImageViewer2.h>
#include <vtkMetaImageReader.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout<<argv[0]<<" "<<"ImageFile(*.mhd)"<<std::endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkMetaImageReader> reader =
            vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkImageViewer2> imageViewer =
            vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);

    imageViewer->SetColorLevel(500);
    imageViewer->SetColorWindow(2000);
    imageViewer->SetSlice(40);
    imageViewer->SetSliceOrientationToXY();
    imageViewer->Render();

    imageViewer->GetRenderer()->SetBackground(1.0,1.0,1.0);
    imageViewer->SetSize(800,600);
    imageViewer->GetRenderWindow()->SetWindowName("DisplayImageExample");

    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
