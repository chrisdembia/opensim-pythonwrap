pushd .
cd ..\su900061
..\src\rra\rra_project\Debug\rra_D.exe -ModelLibrary su900061_D.dll -Actuators su900061_rra.act -Params params.txt -Prefix 900061_42ik_rsw -Tracking su900061_rra.trk
..\src\rra\rra_project\Debug\rra_D.exe -ModelLibrary su900061_D.dll -Actuators su900061_rra.act -Params params.txt -Prefix 900061_42ik_rsw_corrected_by_RRA -Tracking su900061_rra.trk -Correct no
popd
