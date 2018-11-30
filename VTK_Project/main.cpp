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

#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

#include <vtkPolyDataReader.h>
#include <vtkPolyDataNormals.h>
#include <vtkPLYReader.h>
#include <vtkMaskPoints.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout<<argv[0]<<" "<<"*.vtk"<<std::endl;
        return EXIT_FAILURE;
    }

    vtkSmartPointer<vtkPolyDataReader> reader =
            vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();

    vtkSmartPointer<vtkPolyDataNormals> normFilter =
            vtkSmartPointer<vtkPolyDataNormals>::New();
    normFilter->SetInputData(reader->GetOutput());
    normFilter->SetComputePointNormals(1);
    normFilter->SetComputeCellNormals(0);
    normFilter->SetAutoOrientNormals(1);
    normFilter->SetSplitting(0);
    normFilter->Update();

    vtkSmartPointer<vtkMaskPoints> mask =
            vtkSmartPointer<vtkMaskPoints>::New();
    mask->SetInputData(normFilter->GetOutput());
    mask->SetMaximumNumberOfPoints(300);
    mask->RandomModeOn();

    vtkSmartPointer<vtkArrowSource> arrow =
            vtkSmartPointer<vtkArrowSource>::New();
    vtkSmartPointer<vtkGlyph3D> glyph =
            vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputData(mask->GetOutput());
    glyph->SetSourceData(arrow->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleFactor(0.01);

    vtkSmartPointer<vtkPolyDataMapper> originMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkActor> originActor =
            vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);

    vtkSmartPointer<vtkPolyDataMapper> normedMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    normedMapper->SetInputData(normFilter->GetOutput());

    vtkSmartPointer<vtkActor> normedActor =
            vtkSmartPointer<vtkActor>::New();
    normedActor->SetMapper(normedMapper);

    vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    glyphMapper->SetInputData(glyph->GetOutput());

    vtkSmartPointer<vtkActor> glyphActor =
            vtkSmartPointer<vtkActor>::New();
    glyphActor->SetMapper(glyphMapper);
    glyphActor->GetProperty()->SetColor(1.0,0.0,0.0);

    double originalViewport[4] = {0.0, 0.0, 0.33, 1.0};
    double normViewport[4] = {0.33, 0.0, 0.66, 1.0};
    double glphViewport[4] = {0.66, 0.0, 1.0, 1.0};

    vtkSmartPointer<vtkRenderer> originRen =
            vtkSmartPointer<vtkRenderer>::New();
    originRen->SetViewport(originalViewport);
    originRen->AddActor(originActor);
    originRen->ResetCamera();
    originRen->SetBackground(1.0,1.0,1.0);

    vtkSmartPointer<vtkRenderer> normedRen =
            vtkSmartPointer<vtkRenderer>::New();
    normedRen->SetViewport(normViewport);
    normedRen->AddActor(normedActor);
    normedRen->ResetCamera();
    normedRen->SetBackground(1.0,1.0,1.0);

    vtkSmartPointer<vtkRenderer> glyphRen =
            vtkSmartPointer<vtkRenderer>::New();
    glyphRen->SetViewport(glphViewport);
    glyphRen->AddActor(glyphActor);
    glyphRen->AddActor(normedActor);
    glyphRen->ResetCamera();
    glyphRen->SetBackground(1.0,1.0,1.0);

//================================================================================//
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originRen);
    renderWindow->AddRenderer(normedRen);
    renderWindow->AddRenderer(glyphRen);
    renderWindow->SetSize( 640, 480 );
    renderWindow->Render();
    renderWindow->SetWindowName("PolyDataNormal");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
