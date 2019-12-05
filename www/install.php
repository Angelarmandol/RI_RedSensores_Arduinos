<?php
//Create Data base if not exists
	$servername = "localhost";
	$username = "id11681337_root";
	$password = "rootroot";
 
	// Create connection
	$conn = new mysqli($servername, $username, $password);
	// Check connection
	if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	}
 
	// Create database
	$sql = "CREATE DATABASE id11681337_espdemo";
	if ($conn->query($sql) === TRUE) {
	    echo "Database created successfully";
	} else {
	    echo "Error ceando base de datos, codigo: " . $conn->error;
	}
 
	$conn->close();
 
	echo "<br>";
 
	$servername = "localhost";
	$username = "id11681337_root";
	$password = "rootroot";
	$dbname = "id11681337_espdemo";
 
	 
	$conn = new mysqli($servername, $username, $password, $dbname);
 
	if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	}
  
	$sql = "CREATE TABLE logs (
	id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
	station VARCHAR(30),
	digital VARCHAR(30),
	analog VARCHAR(50),
	`Date` DATE NULL,
	`Time` TIME NULL, 
	`TimeStamp` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
	)";
 
	if ($conn->query($sql) === TRUE) {
	    echo "BD instalado OK";
	} else {
	    echo "Error creando la tabla, codigo: " . $conn->error;
	}
 
	$conn->close();
?>