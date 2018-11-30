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

#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <iostream>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>

int main(int argc, char* argv[])
{
//    if(argc < 2)
//    {
//        std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
//        return EXIT_FAILURE;
//    }

    vtkSmartPointer<vtkPoints> points =
            vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0.0,0.0,0.0);
    points->InsertNextPoint(1.0,0.0,0.0);
    points->InsertNextPoint(1.0,1.0,0.0);
    points->InsertNextPoint(0.0,1.0,0.0);
    points->InsertNextPoint(2.0,0.0,0.0);

    vtkSmartPointer<vtkPolygon> polygon =
            vtkSmartPointer<vtkPolygon>::New();
    polygon->GetPointIds()->SetNumberOfIds(4);
    polygon->GetPointIds()->SetId(0,0);
    polygon->GetPointIds()->SetId(1,1);
    polygon->GetPointIds()->SetId(2,2);
    polygon->GetPointIds()->SetId(3,3);

    vtkSmartPointer<vtkTriangle> triangle =
            vtkSmartPointer<vtkTriangle>::New();
    triangle->GetPointIds()->SetId(0,1);
    triangle->GetPointIds()->SetId(1,2);
    triangle->GetPointIds()->SetId(2,4);

    vtkSmartPointer<vtkCellArray> cells =
            vtkSmartPointer<vtkCellArray>::New();
    cells->InsertNextCell(polygon);
    cells->InsertNextCell(triangle);

    vtkSmartPointer<vtkPolyData> polygonPolyData =
            vtkSmartPointer<vtkPolyData>::New();
    polygonPolyData->SetPoints(points);
    polygonPolyData->SetPolys(cells);

    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polygonPolyData);

    vtkSmartPointer<vtkActor> actor =
            vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.5,0.5,0.5);

    // Setup render window
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize( 800, 600 );
    renderWindow->Render();
    renderWindow->SetWindowName("PolyDataNew");

    // Setup render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();

    // Render and start interaction
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
