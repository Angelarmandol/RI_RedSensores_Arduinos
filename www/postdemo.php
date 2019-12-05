

<?php

    $servername = "localhost";
    $username = "id11681337_root";
    $password = "rootroot";
    $dbname = "id11681337_espdemo";
  echo "<html>";

 
    $conn = new mysqli($servername, $username, $password, $dbname);

    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
     echo   "<br>" ;
       echo "<h3>Failed database</h3>";
    }
    echo"<br>" ;
      echo  "<h3>Ok database</h3>";
 

    date_default_timezone_set('America/Los_Angeles');
    $d = date("Y-m-d");
    $t = date("H:i:s");
 
 echo"<br>" ;
 echo  "<h3>contenido</h3> " . $_GET["status"] ;

    if(!empty($_POST['status']) && !empty($_POST['station']))
    {
    	$status = $_POST['status'];
    	$station = $_POST['station'];

      echo  "<br>" ;
      echo "<h3>Entra post</h3>";

	    $sql = "INSERT INTO logs (station, digital, Date, Time)
		
		VALUES ('".$station."', '".$status."', '".$d."', '".$t."')";
 
		if ($conn->query($sql) === TRUE) {
		    echo "OK";
           echo "<br>" ;
        echo"<h3>ok insert</h3>";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
            echo "<br>" ;
       echo "<h3>Fallo el insert</h3>";
		}
	} 

    echo "<br>" ;
    echo "<h3>no entró if</h3>";

 
 
	$conn->close();

    echo"</html>";
?>