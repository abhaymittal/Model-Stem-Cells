from paraview.simple import *

#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

#Creating a render view to display animation
renderView=CreateView('RenderView')
renderView.ViewSize=[605, 837]
renderView.CenterOfRotation =  [24.5, 24.5, 24.5]
renderView.StereoType = 0
renderView.CameraPosition = [118.45578933187856, 79.7077420564557, 219.2573086730089]
renderView.CameraFocalPoint = [24.49999999999999, 24.499999999999986, 24.49999999999991]
renderView.CameraViewUp = [-0.1629648684282408, 0.9670657863727705, -0.195515258957917]
renderView.CameraParallelScale = 58.70793369489452
renderView.Background = [0.32, 0.34, 0.43]
#Creating a CSV Reader
fileList=[];
a=int(raw_input("Enter the number of iteration files"));
for i in range(0,a):
    fileList.append('/home/abhay/ParaView-4.3.1-Linux-64bit/test/iter.csv.'+str(i))

csvRead=CSVReader(FileName=fileList)
tableToPointsFilter=TableToPoints(Input=csvRead)
tableToPointsFilter.XColumn='x'
tableToPointsFilter.YColumn='y'
tableToPointsFilter.ZColumn='z'

#Set up color and opacity transfer functions

scalarLUT = GetColorTransferFunction('scalar')
scalarLUT.EnableOpacityMapping = 1
scalarLUT.RGBPoints = [0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 2.0, 0.0, 1.0, 0.0, 3.0, 1.0, 0.0, 0.0, 4.0, 1.0, 1.0, 1.0]
scalarLUT.NanColor = [0.500008, 0.0, 0.0]
scalarLUT.ScalarRangeInitialized = 1.0


scalarPWF = GetOpacityTransferFunction('scalar')
scalarPWF.Points = [0.0, 0.0, 0.5, 0.0, 1.0, 1.0, 0.5, 0.0, 2.0, 1.0, 0.5, 0.0, 3.0, 1.0, 0.5, 0.0, 3.0, 1.0, 0.5, 0.0, 4.0, 1.0, 0.5, 0.0]
scalarPWF.ScalarRangeInitialized = 1

#Setup vizualization

tableToPointsDisplay=Show(tableToPointsFilter,renderView)
tableToPointsDisplay.ColorArrayName=['POINTS', 'scalar']
tableToPointsDisplay.LookupTable=scalarLUT

#show color legend
tableToPointsDisplay.SetScalarBarVisibility(renderView, True)

# get color legend/bar for scalarLUT in view renderView1
scalarLUTColorBar = GetScalarBar(scalarLUT, renderView)
scalarLUTColorBar.Title = 'scalar'
scalarLUTColorBar.ComponentTitle = ''
