/**********************************************************************

  文件名: 2.1_RenderCylinder.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkStringArray.h>

int main(int argc, char* argv[])
{
//    if(argc < 2)
//    {
//        std::cout<<argv[0]<<" "<<"head%03d.jpg"<<std::endl;
//        return EXIT_FAILURE;
//    }

    vtkSmartPointer<vtkStringArray> fileArray =
            vtkSmartPointer<vtkStringArray>::New();
    char fileName[128];
    for(int i=1; i<100; i++)
    {
        sprintf(fileName,"../data/Head/head%03d.jpg",i);
        vtkstd::string fileStr(fileName);
        fileArray->InsertNextValue(fileStr);
    }

    vtkSmartPointer<vtkJPEGReader> reader =
            vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileNames(fileArray);

    vtkSmartPointer<vtkInteractorStyleImage> style =
            vtkSmartPointer<vtkInteractorStyleImage>::New();

    //显示读取的单幅PNG图像
    vtkSmartPointer<vtkImageViewer2> imageViewer =
            vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    imageViewer->SetSlice(50);
//    imageViewer->SetSliceOrientationToXY();
//    imageViewer->SetSliceOrientationToXZ();
    imageViewer->SetSliceOrientationToYZ();
    imageViewer->SetupInteractor(renderWindowInteractor);
    imageViewer->Render();
    imageViewer->GetRenderer()->SetBackground(1.0,1.0,1.0);

    imageViewer->SetSize(800,600);
    imageViewer->GetRenderWindow()->SetWindowName("ReadSeriesImages1");

    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
