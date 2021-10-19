<?php
$aq = $_POST["aq"];
$data = file_get_contents('https://opendata.epa.gov.tw/Data/Contents/AQI/
');
$rows = explode("\n",$data);
$s = array();
$num=0;
foreach($rows as $row) {
    $s[] = str_getcsv($row);
    $num++;
}

print ("<table><tr><td>縣市</td><td>測值</td></tr>");
for ($i=1;$i<$num-1;$i++)
{
	if()
    $station = $s[$i][0];
    $value = $s[$i][$index];
    print ("<tr><td>$station</td><td>$value</td></tr>");
}
print ("</table>");
?>
