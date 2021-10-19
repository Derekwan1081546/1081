<?php
   $select = $_POST["select"];
   $query = "SELECT " . $select . " FROM books";
   if ( !( $database = mysqli_connect( "localhost", "USERID", "password" ) ) )
       die( "Could not connect to database </body></html>" );
   if ( !mysqli_select_db($database,"products" ) )
       die( "Could not open products database </body></html>" );
   if ( !( $result = mysqli_query($database, $query) ) )
   {
       print( "<p>Could not execute query!</p>" );
       die( mysqli_error() . "</body></html>" );
   }
   mysqli_close( $database );
   print ("<table>");
   while ( $row = mysqli_fetch_row( $result ) )
   {
       print( "<tr>" );
       foreach ( $row as $value )
         print( "<td>$value</td>" );
       print( "</tr>" );
   }
   print ("</table>");
?>
