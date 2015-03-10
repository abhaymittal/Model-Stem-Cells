from paraview.simple import *

#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

#Creating a render view to display animation
renderView=CreateView('RenderView')
renderView.ViewSize = [1217, 837]
renderView.CenterOfRotation = [49.5, 49.5, 49.5]
renderView.StereoType = 0
renderView.CameraPosition = [0.2533115342812731, -7.2933230751984865, 372.1186169832492]
renderView.CameraFocalPoint = [49.50000000000002, 49.50000000000002, 49.50000000000002]
renderView.CameraViewUp = [0.49586925413235977, 0.8391650398537878, 0.22341825953446165]
renderView.CameraParallelScale = 85.73651497465943
renderView.Background = [0.32, 0.34, 0.43]
#Creating a CSV Reader
fileList=[];
a=int(raw_input("Enter the number of iteration files"));
for i in range(0,a):
    fileList.append('/mnt/Entertainment/education/Projects/major_proj_USCP/cellular-automata/iterations/iter.csv.'+str(i))

csvRead=CSVReader(FileName=fileList)
tableToPointsFilter=TableToPoints(Input=csvRead)
tableToPointsFilter.XColumn='x'
tableToPointsFilter.YColumn='y'
tableToPointsFilter.ZColumn='z'

#Set up color and opacity transfer functions

scalarLUT = GetColorTransferFunction('type')
scalarLUT.EnableOpacityMapping = 1
scalarLUT.RGBPoints = [0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 2.0, 0.0, 1.0, 0.0, 3.0, 1.0, 0.0, 0.0, 4.0, 1.0, 1.0, 1.0]
scalarLUT.NanColor = [0.500008, 0.0, 0.0]
scalarLUT.ScalarRangeInitialized = 1.0


scalarPWF = GetOpacityTransferFunction('type')
scalarPWF.Points = [0.0, 0.0, 0.5, 0.0, 1.0, 1.0, 0.5, 0.0, 2.0, 1.0, 0.5, 0.0, 3.0, 1.0, 0.5, 0.0, 3.0, 1.0, 0.5, 0.0, 4.0, 1.0, 0.5, 0.0]
scalarPWF.ScalarRangeInitialized = 1

#Setup vizualization

tableToPointsDisplay=Show(tableToPointsFilter,renderView)
tableToPointsDisplay.ColorArrayName=['POINTS', 'type']
tableToPointsDisplay.LookupTable=scalarLUT

#show color legend
tableToPointsDisplay.SetScalarBarVisibility(renderView, True)

# get color legend/bar for scalarLUT in view renderView1
scalarLUTColorBar = GetScalarBar(scalarLUT, renderView)
scalarLUTColorBar.Title = 'type'
scalarLUTColorBar.ComponentTitle = ''
