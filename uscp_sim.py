from paraview.simple import *

#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

#Creating a render view to display animation
renderView=CreateView('RenderView')
renderView.ViewSize = [1217, 837]
renderView.CenterOfRotation =  [19.5, 19.5, 19.5]
renderView.StereoType = 0
renderView.CameraPosition =  [65.26351752062817, 119.05851804582377, -64.75015285371589]
renderView.CameraFocalPoint = [38.14575246574428, 63.652794990600675, -3.072600922872282]
renderView.CameraViewUp = [0.9491352449466381, -0.2466000227945012, 0.19578231676491256]
renderView.CameraParallelScale = 85.73651497465943
renderView.Background = [0.0, 0.0, 0.0]
#Creating a CSV Reader
fileList=[];
a=int(raw_input("Enter the number of iteration files"));
for i in range(0,a):
    fileList.append('iterations/iter.csv.'+str(i))

csvRead=CSVReader(FileName=fileList)
tableToPointsFilter=TableToPoints(Input=csvRead)
tableToPointsFilter.XColumn='x'
tableToPointsFilter.YColumn='y'
tableToPointsFilter.ZColumn='z'

#Set up color and opacity transfer functions

scalarLUT = GetColorTransferFunction('type')
scalarLUT.EnableOpacityMapping = 1
scalarLUT.RGBPoints =[0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 2.0, 0.0, 1.0, 0.0, 3.0, 1.0, 0.0, 0.0, 4.0, 1.0, 1.0, 1.0]
scalarLUT.NanColor = [0.500008, 0.0, 0.0]
scalarLUT.ScalarRangeInitialized = 1.0


scalarPWF = GetOpacityTransferFunction('type')
scalarPWF.Points =[0.0, 0.0, 0.5, 0.0, 1.0, 0.3, 0.5, 0.0, 2.0, 0.7, 0.5, 0.0, 3.0, 0.7, 0.5, 0.0, 4.0, 1.0, 0.5, 0.0]
scalarPWF.ScalarRangeInitialized = 1

#Setup vizualization

tableToPointsDisplay=Show(tableToPointsFilter,renderView)
tableToPointsDisplay.ColorArrayName=['POINTS', 'type']
tableToPointsDisplay.LookupTable=scalarLUT
tableToPointsDisplay.PointSize = 2.0

#show color legend
tableToPointsDisplay.SetScalarBarVisibility(renderView, True)

# get color legend/bar for scalarLUT in view renderView1
scalarLUTColorBar = GetScalarBar(scalarLUT, renderView)
scalarLUTColorBar.Title = 'type'
scalarLUTColorBar.ComponentTitle = ''

# create a new 'Outline'
envOutline = Outline(Input=tableToPointsFilter)

#display the outline
envOutDisplay = Show(envOutline, renderView)
envOutDisplay.ColorArrayName = [None, '']
envOutDisplay.PointSize = 2.0
