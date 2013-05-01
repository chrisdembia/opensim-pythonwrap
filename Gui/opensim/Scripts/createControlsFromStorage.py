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
#
# Author(s): Ayman Habib, Jen Hicks
# Stanford University
#
# This example loads controls from a storage file and creates an xml file 
# that has a ControlSet. The column labels are assumed to be names of 
# actuators, unless they have a trailing "_min", or "_max" then they're used
# as control constraints. If no min or max is specified in the file then the same
# value is used for Control's min, max and value.

# Utils contains tools to browse for files and folders
import org.opensim.utils as utils
import os

# Load the setup file
print "Acquiring file for Control profile"

# Prompts user to select file if above does not exist
controlProfileStore = "doesnotexistfile.sto"
if not os.path.exists(controlProfileStore):
	controlProfileStore = utils.FileUtils.getInstance().browseForFilename(".sto", "Select the storage file for controls profile", 1)
print controlProfileStore
controlStorage = modeling.Storage(controlProfileStore)

controlProfileXml = "doesnotexistfile.xml"
if not os.path.exists(controlProfileXml):
	controlProfileXml = utils.FileUtils.getInstance().browseForFilenameToSave(".xml", "Select the xml file for controls", 1, "controls.xml")
print controlProfileXml

#Invoke constructor of ControlSet that takes a Storage as input.
#if that's all what you need, you can stop here and write the result to file
csetRaw = modeling.ControlSet(controlStorage)

# Now cycle thru the controls and foreach
#	find name, if not ending in _min or _max then
#	if name_min exists then use it as minValue otherwise use value itself as minValue
#	if name_max exists then use it as maxValue otherwise use value itself as maxValue
#	remove all controls that end in _min or _max and write to file

# number of controls 
sz = csetRaw.getSize()
# column labels are all controls, min, max + time
lbls = controlStorage.getColumnLabels()
nLabels = lbls.getSize()-1

#for all controls in the set do this
for i in range (0, nLabels):
	csi = csetRaw.get(i)
	csiL = modeling.ControlLinear.safeDownCast(csi)
	controlName = csi.getName()
	minControlName = controlName+'_min'
	minControlIndex = -1
	maxControlName = controlName+'_max'
	maxControlIndex = -1
	# if name doesn't contain _min or _max
	if (controlName.find('_min')==-1 and controlName.find('_max')==-1):
		minControlIndex = csetRaw.getIndex(minControlName)
		maxControlIndex = csetRaw.getIndex(maxControlName)
		currentMin = 10000000
		currentMax = -10000000
		if (minControlIndex!= -1):
			csiL_min = modeling.ControlLinear.safeDownCast(csetRaw.get(minControlIndex))
			nodeSet = csiL.getControlValues()
			nodeSetSize = nodeSet.getSize()
			for nodeNum in range(0, nodeSetSize-1):
				clNode = nodeSet.get(nodeNum)
				clNodeTime = clNode.getTime()
				minValue = csiL_min.getControlValue(clNodeTime)
				csiL.setControlValueMin(clNodeTime, minValue)
				if (minValue < currentMin):
					currentMin = minValue
		else:
			nodeSet = csiL.getControlValues()
			nodeSetSize = nodeSet.getSize()
			for nodeNum in range(0, nodeSetSize-1):
				clNode = nodeSet.get(nodeNum)
				clNodeTime = clNode.getTime()
				minValue = csiL.getControlValue(clNodeTime);
				csiL.setControlValueMin(clNodeTime, minValue)
				if (minValue < currentMin):
					currentMin = minValue
		csiL.setDefaultParameterMin(currentMin)
		# repeat for max
		if (maxControlIndex!=-1):
			csiL_max = modeling.ControlLinear.safeDownCast(csetRaw.get(maxControlIndex))
			nodeSet = csiL.getControlValues()
			nodeSetSize = nodeSet.getSize()
			for nodeNum in range(0, nodeSetSize-1):
				clNode = nodeSet.get(nodeNum)
				clNodeTime = clNode.getTime()
				maxValue = csiL_max.getControlValue(clNodeTime)
				csiL.setControlValueMax(clNodeTime, maxValue)
				if (maxValue > currentMax):
					currentMax = maxValue
		else:
			nodeSet = csiL.getControlValues()
			nodeSetSize = nodeSet.getSize()
			for nodeNum in range(0, nodeSetSize-1):
				clNode = nodeSet.get(nodeNum)
				clNodeTime = clNode.getTime()
				maxValue = csiL.getControlValue(clNodeTime)
				csiL.setControlValueMax(clNodeTime, maxValue)
				if (maxValue > currentMax):
					currentMax = maxValue
		csiL.setDefaultParameterMax(currentMax)

#remove entries that has trailing _min or _max
for i in range (0, lbls.getSize()):
	label = lbls.getitem(i)
	if (label.find('_min')==-1 and label.find('_max')==-1):
		continue
	idx = csetRaw.getIndex(label)
	csetRaw.remove(idx)

# Write output to xml file
csetRaw.print(controlProfileXml)


