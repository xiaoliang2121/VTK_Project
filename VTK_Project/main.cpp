/**********************************************************************

  文件名: 2.1_RenderCylinder.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkCellArray.h>

int main(int argc, char* argv[])
{
    double X[3] = {1.0,0.0,0.0};
    double Y[3] = {0.0,0.0,1.0};
    double Z[3] = {0.0,0.0,0.0};

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

    for(int i=0; i<3; i++)
    {
        vtkIdType pid;
        pid = points->InsertNextPoint(X[i],Y[i],Z[i]);
        vertices->InsertNextCell(1,&pid);
    }

    vtkSmartPointer<vtkPolyData> polydata =
            vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->SetVerts(vertices);

    vtkSmartPointer<vtkPolyDataWriter> writer =
            vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName("triangleVertex.vtk");
    writer->SetInputData(polydata);
    writer->Write();

    return EXIT_SUCCESS;
}
