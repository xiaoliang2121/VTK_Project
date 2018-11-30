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
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkFloatArray.h>
#include <vtkPlaneSource.h>
#include <vtkCellDataToPointData.h>
#include <vtkPointDataToCellData.h>
#include <vtkDataSet.h>
#include <vtkLookupTable.h>
#include <vtkTransformTextureCoords.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>

int main(int argc, char* argv[])
{
//    if(argc < 2)
//    {
//        std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
//        return EXIT_FAILURE;
//    }

    vtkSmartPointer<vtkPlaneSource> gridSource =
            vtkSmartPointer<vtkPlaneSource>::New();
    gridSource->SetXResolution(3);
    gridSource->SetYResolution(3);
    gridSource->Update();
    vtkSmartPointer<vtkPolyData> grid = gridSource->GetOutput();

    vtkSmartPointer<vtkFloatArray> cellScalars =
            vtkSmartPointer<vtkFloatArray>::New();
    vtkSmartPointer<vtkFloatArray> cellVectors =
            vtkSmartPointer<vtkFloatArray>::New();
    cellVectors->SetNumberOfComponents(3);

    for(int i=0; i<9; i++)
    {
        cellScalars->InsertNextValue(i+1);
        cellVectors->InsertNextTuple3(0.0,0.0,0.0);
    }

    grid->GetCellData()->SetScalars(cellScalars);
    grid->GetCellData()->SetVectors(cellVectors);

    vtkSmartPointer<vtkLookupTable> lut =
            vtkSmartPointer<vtkLookupTable>::New();
    lut->SetNumberOfTableValues(10);
    lut->Build();
    lut->SetTableValue(0     , 0     , 0     , 0, 1);
    lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);
    lut->SetTableValue(2, 1.0000, 0.3882, 0.2784, 1);
    lut->SetTableValue(3, 0.9608, 0.8706, 0.7020, 1);
    lut->SetTableValue(4, 0.9020, 0.9020, 0.9804, 1);
    lut->SetTableValue(5, 1.0000, 0.4900, 0.2500, 1);
    lut->SetTableValue(6, 0.5300, 0.1500, 0.3400, 1);
    lut->SetTableValue(7, 0.9804, 0.5020, 0.4471, 1);
    lut->SetTableValue(8, 0.7400, 0.9900, 0.7900, 1);
    lut->SetTableValue(9, 0.2000, 0.6300, 0.7900, 1);

/// =============================================================================
    vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(grid);
//    mapper->SetScalarModeToUseCellData();
//    mapper->SetScalarModeToUsePointFieldData();
//    mapper->ColorByArrayComponent("Filed",0);
//    mapper->SelectColorArray("Filed");
//    mapper->SetScalarRange(1,5);
//    mapper->SetLookupTable(lut);

    // 测试单元属性数据转点属性数据
    vtkSmartPointer<vtkCellDataToPointData> convert =
        vtkSmartPointer<vtkCellDataToPointData>::New();
    convert->SetInputData(grid);
    convert->SetPassCellData(true);
    convert->Update();
    mapper->SetInputData((vtkPolyData*)convert->GetOutput());

    mapper->SetScalarRange(0,9);
    mapper->SetLookupTable(lut);

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
    renderWindow->SetWindowName("PolyDataAttribute");

    // Setup render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();

    // Render and start interaction
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
