<?php
   if( $_GET["Heading"]) {
    $heading = $_GET['Heading'];
    $Gx = $_GET['Gx'];
    $Gy = $_GET['Gy'];
    $Gz = $_GET['Gz'];
    $Ax = $_GET['Ax'];
    $Ay = $_GET['Ay'];
    $Az = $_GET['Az'];
    $Mx = $_GET['Mx'];
    $My = $_GET['My'];
    $Mz = $_GET['Mz'];
    
    $servername = "localhost";
    $username = "esp";
    $password = "@rduino2560";
    $dbname = "esp";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
else
{
    $sql =  "INSERT INTO `esp`(`Time`,`Heading`, `Gx`, `Gy`, `Gz`, `Ax`, `Ay`, `Az`, `Mx`, `My`, `Mz`) VALUES (NOW(),$heading, $Gx, $Gy, $Gz, $Ax, $Ay, $Az, $Mx, $My,$Mz)";
    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

}

   }
?>

//http://localhost/esp/?Heading=35.25&Gx=12.31&Gy=123.42&Gz=41.41&Ax=123.41&Ay=56.43&Az=51.51&Mx=51.52&My=52.41&Mz=23.52