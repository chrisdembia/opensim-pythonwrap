# This example script runs multiple inverse kinematics trials for the leg39 model. To see the results 
# load the model and ik output in the GUI.
# The script prompts the user for input files.

# Import needed packages
# COMMENT
import java.io as io 

# COMMENT
import org.opensim.utils as utils

# More graceful handling of exceptions thrown by tools, may be taken out in production
modeling.OpenSimObject.setDebugLevel(3)

# Browse for Directory containing trc files to process
print "Acquire folder that contains trc files"
trcDataFolder = utils.FileUtils.getInstance().browseForFolder()
print trcDataFolder

# Load the setup file
print "Acquire setup file"
setupFile = utils.FileUtils.getInstance().browseForFilename(".xml", "setup file for tool", 1)
print setupFile

# Select folder to store output results
print "Acquire folder to store the IK results output files"
resultsFolder = utils.FileUtils.getInstance().browseForFolder()
print resultsFolder

# Initialize InverseKinematicsTool from setup file
ikTool = modeling.InverseKinematicsTool(setupFile)
print "Created InverseKinematicsTool"

# Load the model to be used and and initialize
print "Acquire model"
modelFilename = utils.FileUtils.getInstance().browseForFilename(".osim", "Model file for tool", 1)
model = modeling.Model(modelFilename)
model.initSystem()
print "Created and initialized model"

# Tell the IK tool to use the model
ikTool.setModel(model)

# Cycle thru the trc files in trcDataFolder, set each as markerDataFileName
# change corresponding output file and repeat
trcFolder = io.File(trcDataFolder)
      
trcFiles = trcFolder.list() 
  
for x in range(len(trcFiles)): 
    if trcFiles[x].endswith(".trc"):
	
		  # Set name of output motion
		  print "Processing "+trcFiles[x]
		  outFile = trcFiles[x].replace('.trc', '_ik.sto')
		  trialSetupFile = trcFiles[x].replace('.trc', 'ik_setup.xml')
		  
		  # Set name of input trc file and output motion in tool
		  ikTool.setMarkerDataFileName(trcDataFolder+'\\'+trcFiles[x])
		  ikTool.setOutputMotionFileName(resultsFolder+'\\'+outFile)
		  
		  # Use the trc file to get the start and end times
		  markerData = modeling.MarkerData(trcDataFolder+'\\'+trcFiles[x])
		  ikTool.setStartTime(markerData.getStartFrameTime())
		  ikTool.setEndTime(markerData.getLastFrameTime())
		  
		  # Run the tool
		  print "Runnning trial file "+ikTool.getMarkerDataFileName()+" Output:"+ikTool.getOutputMotionFileName()
		  ikTool.run()
		  print "Finished processing trial "+trcFiles[x]
		  
		  # Save the setup file
		  trialSetupFile = trcFiles[x].replace('.trc', '_IK_Setup.xml')
		  ikTool.print(resultsFolder+'\\'+trialSetupFile)
		  
		  


