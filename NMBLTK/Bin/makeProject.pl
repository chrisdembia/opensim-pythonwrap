#!/usr/bin/perl -w
#

use Cwd;
$curFolder = cwd;

# Parse curFolder to extract model name
@dirArray = split(/\\|\//, $curFolder);
$subjectName = $dirArray[$#dirArray];
chomp($subjectName);

use locale;

my $CapSubjectName = "\u$subjectName";
my $suCapSubjectName = "su".$CapSubjectName;

chomp($subjectName);
%filemap = (
	"template.vcproj" => $suCapSubjectName.".vcproj",
	"template.sln" => $suCapSubjectName.".sln",
	"template.dsw" => $suCapSubjectName.".dsw",
	"template.dsp" => $suCapSubjectName.".dsp",
	"template.h" => $suCapSubjectName.".h",
	"template.cpp" => $suCapSubjectName.".cpp",
	"template_Forward.cpp" => $suCapSubjectName."_Forward.cpp",
	"template_Perturb.cpp" => $suCapSubjectName."_Perturb.cpp",
	"sdufuncs_darryl.c" => "sdufuncs_darryl.c"
);
my $templateDir = $ENV{RDI_INSTALL}.'/Template/';

if (mkdir('Results',0777)==0){
	print "Err : $!. Directory could not be created\n"; 
}
print "Created directory Results to save analysis results\n";

while ( my ($key, $value) = each(%filemap) ) {
		my $templateFile = $templateDir.$key;
		my $subjectFile = $value;
	if(open(TEMPL_FH, "<$templateFile")) {
		if(open(SUBJECT_FH, ">$subjectFile")) {
		#Loop thru and substitute _template_ with $subjectName
		while(<TEMPL_FH>){
			$nextLine = $_;
			$nextLine =~ s/_template_/$subjectName/g;
			$nextLine =~ s/_Template_/$CapSubjectName/g;
			print SUBJECT_FH $nextLine;
		}
		close(SUBJECT_FH);
		print "Created file $subjectFile\n";
		}
		else {
			die "Cannot open subject file";
		}
		close(SUBJECT_FH);
	}
	else {
		die "Cannot find template file";
	}
};
