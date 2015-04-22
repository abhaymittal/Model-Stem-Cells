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


# create a new 'Outline'
envOutline = Outline(Input=tableToPointsFilter)

#display the outline
envOutDisplay = Show(envOutline, renderView)
envOutDisplay.ColorArrayName = [None, '']
envOutDisplay.PointSize = 2.0


#Display Annotations
# 'Annotate ECM Data'
annotateECMData = AnnotateAttributeData(Input=tableToPointsFilter)
annotateECMData.ArrayAssociation = 'Point Data'
annotateECMData.ArrayName = 'type'
annotateECMData.ElementId = 1
annotateECMData.Prefix = 'ECM Fiber    : '
annotateECMDataDisplay = Show(annotateECMData, renderView)
annotateECMDataDisplay.Color = [0.0196078431372549, 0.32941176470588235, 1.0]
annotateECMDataDisplay.FontSize = 10
annotateECMDataDisplay.Position = [0.718292, 0.683952]

# 'Annotate Normal Cell Data'
annotateNormalData = AnnotateAttributeData(Input=tableToPointsFilter)
annotateNormalData.ArrayAssociation = 'Point Data'
annotateNormalData.ArrayName = 'type'
annotateNormalData.ElementId = 2
annotateNormalData.Prefix = 'Normal Cell : '
annotateNormalDataDisplay = Show(annotateNormalData, renderView)
annotateNormalDataDisplay.Color = [0.0, 1.0, 0.0]
annotateNormalDataDisplay.FontSize = 10
annotateNormalDataDisplay.Position = [0.7182922357723578, 0.7620951550255537]


# create a new 'Annotate TA Cell Data'
annotateTAData = AnnotateAttributeData(Input=tableToPointsFilter)
annotateTAData.ArrayAssociation = 'Point Data'
annotateTAData.ArrayName = 'type'
annotateTAData.ElementId = 3
annotateTAData.Prefix = 'TA Cell         : '
annotateTADataDisplay = Show(annotateTAData, renderView)
annotateTADataDisplay.Color = [1.0, 0.0, 0.0]
annotateTADataDisplay.FontSize = 10
annotateTADataDisplay.Position = [0.718292, 0.835349]

# create a new 'Annotate Stem Cell Data'
annotateStemCellData = AnnotateAttributeData(Input=tableToPointsFilter)
annotateStemCellData.ArrayAssociation = 'Point Data'
annotateStemCellData.ArrayName = 'type'
annotateStemCellData.ElementId = 4
annotateStemCellData.Prefix = 'Stem Cell     : '
annotateStemCellDataDisplay = Show(annotateStemCellData, renderView)
annotateStemCellDataDisplay.Color = [1.0, 1.0, 1.0]
annotateStemCellDataDisplay.FontSize = 10
annotateStemCellDataDisplay.Position = [0.718292, 0.91431]
