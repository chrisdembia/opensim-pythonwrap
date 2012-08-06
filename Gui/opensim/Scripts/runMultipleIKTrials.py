# ----------------------------------------------------------------------- #
# The OpenSim API is a toolkit for musculoskeletal modeling and           #
# simulation. See http://opensim.stanford.edu and the NOTICE file         #
# for more information. OpenSim is developed at Stanford University       #
# and supported by the US National Institutes of Health (U54 GM072970,    #
# R24 HD065690) and by DARPA through the Warrior Web program.             #
#                                                                         #   
# Copyright (c) 2005-2012 Stanford University and the Authors             #
#                                                                         #   
# Licensed under the Apache License, Version 2.0 (the "License");         #
# you may not use this file except in compliance with the License.        #
# You may obtain a copy of the License at                                 #
# http://www.apache.org/licenses/LICENSE-2.0.                             #
#                                                                         # 
# Unless required by applicable law or agreed to in writing, software     #
# distributed under the License is distributed on an "AS IS" BASIS,       #
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or         #
# implied. See the License for the specific language governing            #
# permissions and limitations under the License.                          #
# ----------------------------------------------------------------------- #

# This example script runs multiple inverse kinematics trials for the leg39 model. To see the results 
# load the model and ik output in the GUI.
# The script can either use the specified input and output folders/files, or you can prompt the user.

# Import needed packages
# COMMENT
import java.io as io 

# More graceful handling of exceptions thrown by tools, may be taken out in production
modeling.OpenSimObject.setDebugLevel(3)

# Browse for Directory containing trc files to process
# Or use the commented line to allow the user to browse for the folder
print "Acquire folder that contains trc files"
trcDataFolder = getScriptsDir()+"\\testData\\Subject01\\Marker_Data\\"
print trcDataFolder

# Load the setup file
# Or use the commented line to allow the user to browse for the folder
print "Acquire setup file"
setupFile = getScriptsDir()+"\\testData\\Subject01\\Generic_Setup_leg39_InverseKinematics.xml"
print setupFile

# Select folder to store output results
print "Acquire folder that contains output files"
resultsFolder = getScriptsDir()+"\\testData\\Subject01\\IK_Results\\"
print resultsFolder

# Initialize InverseKinematicsTool from setup file
ikTool = modeling.InverseKinematicsTool(setupFile)
print "Created InverseKinematicsTool"

# Create the model to be used and and initialize
model = modeling.Model(getScriptsDir()+"\\testData\\Subject01\\Subject01.osim")
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
		  
		  # Set name of input trc file and output motion in tool
		  ikTool.setMarkerDataFileName(trcDataFolder+trcFiles[x])
		  ikTool.setOutputMotionFileName(resultsFolder+outFile)
		  
		  # Use the trc file to get the start and end times
		  markerData = modeling.MarkerData(trcDataFolder+trcFiles[x])
		  ikTool.setStartTime(markerData.getStartFrameTime())
		  ikTool.setEndTime(markerData.getLastFrameTime())
		  
		  # Run the tool
		  print "Running trial file "+ikTool.getMarkerDataFileName()+" Output:"+ikTool.getOutputMotionFileName()
		  ikTool.run()
		  print "Finished processing trial "+trcFiles[x] 
		  
	      # Save the setup file
		  trialSetupFile = trcFiles[x].replace('.trc', '_IK_Setup.xml')
		  ikTool.print(resultsFolder+trialSetupFile)
		  


