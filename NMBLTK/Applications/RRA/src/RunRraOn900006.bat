pushd .
cd ..\..\WorkflowExample
..\RRA\src\rra\rra_project\Debug\rra_D.exe -ModelLibrary su900006_D.dll -Actuators su900006_rra.act -Params params.txt -Prefix 900006_13ik -Tracking su900006_rra.trk
..\RRA\src\rra\rra_project\Debug\rra_D.exe -ModelLibrary su900006_D.dll -Actuators su900006_rra.act -Params params.txt -Prefix 900006_13ik_corrected_by_RRA -Tracking su900006_rra.trk -Correct no
popd
