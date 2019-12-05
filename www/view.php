<!DOCTYPE html>
<html>
<head>
<meta http-equiv="refresh" content="5">
</head>
<body>
<style>
#c4ytable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 70%;
}
 //tabla
#c4ytable td, #c4ytable th {
    border: 1px solid #ddd;
    padding: 8px;
}
 //renlgon
#c4ytable tr:nth-child(even)
{background-color: #f2f2f2;}
 
#c4ytable tr:hover {background-color: #ddd;}
 
#c4ytable th {
    padding-top: 5px;
    padding-bottom: 5px;
    text-align: left;
    background-color: #0066cc;
    color: white;
}
</style>
 
<?php
  
    $servername = "localhost";
    $username = "id11681337_root";
    $password = "rootroot";
    $dbname = "id11681337_espdemo";
 
    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Error al conectar con la base de datos, codigo: " . $conn->connect_error);
        echo "<a href='install.php'>If first time running click here to install database</a>";
    }
?> 
 
 
<div id="cards" class="cards">
 
<?php 
    $sql = "SELECT * FROM logs ORDER BY id DESC";
    if ($result=mysqli_query($conn,$sql))
    {

      echo "<TABLE id='c4ytable'>";
      echo "<TR><TH>Registro</TH><TH>Estación</TH><TH>Digital</TH><TH>Analog</TH><TH>Date</TH><TH>Time</TH></TR>";
      while ($row=mysqli_fetch_row($result))
      {
        echo "<TR>";
        echo "<TD>".$row[0]."</TD>";
        echo "<TD>".$row[1]."</TD>";
        echo "<TD>".$row[2]."</TD>";
        echo "<TD>".$row[3]."</TD>";
        echo "<TD>".$row[4]."</TD>";
        echo "<TD>".$row[5]."</TD>";
        echo "</TR>";
      }
      echo "</TABLE>";

      mysqli_free_result($result);
    }
 
    mysqli_close($conn);
?>
</body>
</html>