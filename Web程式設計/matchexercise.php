<?php
    $search = "tinin@saturn.yzu.edu.tw";
	if(preg_match("/^([p-9a-zA-Z]+)@(.*))$/",$search, $match))
	{
		print( "<p>Match[0]:". $match[0]."</p>" );
		print( "<p>Match[1]:". $match[1]."</p>" );
		print( "<p>Match[2]:". $match[2]."</p>" );
	}
	$search="140.138..145.75";
	if(preg_match("/^(\d+,\d+)\.(\d+)\.(\d+)$/",$search, $match))
	{
		print( "<p>Match[0]:". $match[0]."</p>" );
		print( "<p>Match[1]:". $match[1]."</p>" );
		print( "<p>Match[2]:". $match[2]."</p>" );
		print( "<p>Match[3]:". $match[3]."</p>" );
	 }
?>     

