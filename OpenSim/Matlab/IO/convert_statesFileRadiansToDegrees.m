function convert_statesFileRadiansToDegrees( inputFileName, outputFileName )

if nargin < 2
    inputFileNameExtension = inputFileName( end - 3: end );
    if strcmpi( inputFileNameExtension, '.sto' )
        outputFileName = [inputFileName( 1: end - 4 ) '_inDegrees.sto'];
    else
        outputFileName = [inputFileName '_inDegrees.sto'];
    end
end

q = read_motionFile( inputFileName );

labelsOfColumnsToConvertToDegrees = { 'pelvis_tilt' 'pelvis_list' 'pelvis_rotation' ...
    'hip_flexion_r' 'hip_adduction_r' 'hip_rotation_r' 'knee_angle_r' 'tib_pat_r_r1' ...
    'ankle_angle_r' 'subtalar_angle_r' 'mtp_angle_r' 'hip_flexion_l' 'hip_adduction_l' ...
    'hip_rotation_l' 'knee_angle_l' 'tib_pat_l_r1' 'ankle_angle_l' 'subtalar_angle_l' ...
    'mtp_angle_l' 'lumbar_extension' 'lumbar_bending' 'lumbar_rotation' ...
    'pelvis_tilt_u' 'pelvis_list_u' 'pelvis_rotation_u' 'hip_flexion_r_u' ...
    'hip_adduction_r_u' 'hip_rotation_r_u' 'knee_angle_r_u' 'tib_pat_r_r1_u' ...
    'ankle_angle_r_u' 'subtalar_angle_r_u' 'mtp_angle_r_u' 'hip_flexion_l_u' ...
    'hip_adduction_l_u' 'hip_rotation_l_u' 'knee_angle_l_u' 'tib_pat_l_r1_u' ...
    'ankle_angle_l_u' 'subtalar_angle_l_u' 'mtp_angle_l_u' 'lumbar_extension_u' ...
    'lumbar_bending_u' 'lumbar_rotation_u' };

indicesOfColumnsToConvertToDegrees = [];
for i = 1:length( labelsOfColumnsToConvertToDegrees )
    indicesOfColumnsToConvertToDegrees = [indicesOfColumnsToConvertToDegrees ...
        find( strcmp( q.labels, labelsOfColumnsToConvertToDegrees(i) ) )];
end

factorForConvertingFromRadiansToDegrees = 180.0 / pi;

q.data( :, indicesOfColumnsToConvertToDegrees ) = ...
    q.data( :, indicesOfColumnsToConvertToDegrees ) .* ...
    factorForConvertingFromRadiansToDegrees;

write_motionFile( q, outputFileName );
