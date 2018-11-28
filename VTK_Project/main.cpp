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
#include <vtkActor.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout<<argv[0]<<" "<<"BMP-File(*.bmp)"<<std::endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkBMPReader> reader =
            vtkSmartPointer<vtkBMPReader>::New();
    std::cout<<"Modification Time of reader (After New()): "
            <<reader->GetMTime()<<std::endl;
    reader->SetFileName(argv[1]);
    std::cout<<"Modification Time of reader (After SetFileName()): "
            <<reader->GetMTime()<<std::endl;

    vtkImageData *imageData = reader->GetOutput();
    std::cout<<"Modification Time of reader (After GetOutput()): "
            <<reader->GetMTime()<<std::endl;
    reader->Update();
    std::cout<<"Modification Time of reader (After Update()): "
            <<reader->GetMTime()<<std::endl;

    int extent[6];
    imageData->GetExtent(extent);
    std::cout<<"Extent of image: "<<extent[0]<<" "
        <<extent[1]<<" "<<extent[2]<<" "<<extent[3]<<" "
        <<extent[4]<<" "<<extent[5]<<" "<<std::endl;

    vtkSmartPointer<vtkImageViewer2> viewer =
            vtkSmartPointer<vtkImageViewer2>::New();

    //////////////////////////////////////渲染引擎部分////////////////////////////////////
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);

//    vtkSmartPointer<vtkRenderer> renderer =
//        vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(actor);
//    renderer->SetBackground(1.0, 1.0, 1.0);

//    vtkSmartPointer<vtkRenderWindow> renWin =
//        vtkSmartPointer<vtkRenderWindow>::New();
//    renWin->AddRenderer(renderer);
//    renWin->SetSize( 800, 600 );
//    renWin->Render();
//    renWin->SetWindowName("vtkPipelineDemo");

    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    viewer->SetupInteractor(interactor);
    viewer->SetInputData(imageData);
    viewer->Render();

    viewer->SetSize(800,600);
    viewer->GetRenderWindow()->SetWindowName("vtkPipelineExecute");

    interactor->Initialize();
    interactor->Start();

    return EXIT_SUCCESS;
}
