<?php
$aq = $_POST["aq"];
header("Access-Control-Allow-Origin: *");
$context  = stream_context_create(array('http' => array('header' => 'Accept: application/xml')));
$url = "http://opendata.epa.gov.tw/webapi/Data/REWIQA/?$format=xml" ;
$xml = file_get_contents($url, false, $context);
$xml = simplexml_load_string($xml);
$time = $xml->Data->PublishTime;
print ("<p>Update Time: $time ; 空汙指標:$aq</p>");
print ("<table><tr><td>測站</td><td>測值</td></tr>");
foreach ($xml->Data as $key)
{
    $station = $key->SiteName;
    $value = $key->{$aq};
    print ("<tr><td>$station</td><td>$value</td></tr>");
}
print ("</table>");
?>
