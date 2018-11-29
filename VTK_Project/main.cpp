/**********************************************************************

  文件名: 2.1_RenderCylinder.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkJPEGWriter.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout<<argv[0]<<" "<<"PNG-File(*.png)"<<std::endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkPNGReader> reader =
            vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(argv[1]);

    vtkSmartPointer<vtkInteractorStyleImage> style =
            vtkSmartPointer<vtkInteractorStyleImage>::New();

    //显示读取的单幅PNG图像
    vtkSmartPointer<vtkImageViewer2> imageViewer =
            vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    imageViewer->SetupInteractor(renderWindowInteractor);
    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();

    imageViewer->SetSize(800,600);
    imageViewer->GetRenderWindow()->SetWindowName("ReadWriteSingleImage");

    //保存成JPG图像
    vtkSmartPointer<vtkJPEGWriter> writer =
            vtkSmartPointer<vtkJPEGWriter>::New();
    writer->SetFileName("VTK-logo.jpg");
    writer->SetInputConnection(reader->GetOutputPort());
    writer->Write();

    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
